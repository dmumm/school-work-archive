#include "page.h"
#include <stdlib.h>  // For malloc, free

// Helper function to align size to the nearest multiple of page size
static size_t align_to_page_size(size_t size)
{
    fprintf(stderr, "align_to_page_size\n");
    size_t page_size = sysconf(_SC_PAGESIZE);
    return (size + page_size - 1) & ~(page_size - 1);
}

// create a new page
page_t *create_page(size_t object_size)
{
    fprintf(stderr, "create_page\n");

    // Get the system's page size
    size_t sys_page_size = sysconf(_SC_PAGESIZE);
    assert(sys_page_size == PAGESIZE);

    // Calculate how many blocks can fit in a system page.
    // This calculation includes space for the block metadata and the block itself.
    size_t block_plus_metadata_size = sizeof(block_metadata_t) + object_size;
    size_t expected_block_count = (sys_page_size - sizeof(page_t)) / block_plus_metadata_size;

    // Ensure there's space for at least one block
    if (expected_block_count == 0) {
        expected_block_count = 1;
    }

    // Calculate the required size for the page
    size_t page_size = align_to_page_size
                        (  sizeof(page_t)
                        + (sizeof(block_metadata_t) * expected_block_count)
                        + (object_size * expected_block_count));

    page_t *page = (page_t *)mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    assert(page != MAP_FAILED);
    if (page == MAP_FAILED) return NULL;

    // Initialize the page structure
    page->object_size = object_size;
    page->block_count = (( page_size - sizeof(page_t)                        )
                      - (( sizeof(block_metadata_t) * expected_block_count )))
                      / (( object_size                                     ));
    page->free_block_count = page->block_count;
    page->free_list = NULL;
    page->next = NULL;

    // Allocate memory for the metadata array
    page->metadata = (block_metadata_t *)mmap(NULL, page->block_count * sizeof(block_metadata_t),
                                              PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(page->metadata != MAP_FAILED);

    for (size_t i = 0; i < page->block_count; ++i) {
        page->metadata[i].is_free = 1;  // Mark all blocks as free initially
    }

    // Allocate memory for the blocks
    page->blocks = (char *)mmap(NULL, page->block_count * object_size,
                                PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(page->blocks != MAP_FAILED);

    return page;
}

// Free a page
void free_page(page_t *page)
{
    fprintf(stderr, "free_page\n");
    assert(page != NULL);
    if (page == NULL) return;

    // Calculate the size of the memory to unmap.
    // TODO: Doublecheck correct number
    size_t size_to_unmap = sizeof(page_t) + (page->block_count * page->object_size);

    //  free the memory
    if (munmap(page, size_to_unmap) == -1) {
        assert(0);  // munmap failed
    }
}


// Add a block to the page's free list
void add_block_to_page_free_list(page_t *page, void *block)
{
    fprintf(stderr, "add_block_to_page_free_list\n");

    if (page == NULL || block == NULL) return;

    free_list_node_t *new_node = (free_list_node_t *)block;
    new_node->next = page->free_list;
    page->free_list = new_node;
    page->free_block_count++;
}

// Remove a block from the page's free list
void *remove_block_from_page_free_list(page_t *page)
{
    fprintf(stderr, "remove_block_from_page_free_list\n");
    if (page == NULL || page->free_list == NULL) return NULL;

    free_list_node_t *node = page->free_list;
    page->free_list = node->next;
    page->free_block_count--;

    return node;
}

// Check if a page is full
int is_page_full(const page_t *page)
{
    fprintf(stderr, "is_page_full\n");
    if (page == NULL) {
        return 1;  // Consider an empty page as 'full' to prevent usage
    }

    return (page->free_block_count == 0);
}

size_t get_block_size(void *ptr)
{
    fprintf(stderr, "get_block_size\n");
    // Uses object_size in page_t to determine the size of the block
    page_t *page = (page_t *)((char*)ptr - sizeof(page_t)); // Corrected pointer arithmetic
    return page->object_size;
}

int is_block_in_page(page_t *page, void *ptr)
{
    fprintf(stderr, "is_block_in_page\n");
    char *start = page->blocks;
    char *end = start + (page->block_count * page->object_size);

    uintptr_t ptr_val = (uintptr_t)ptr;
    uintptr_t start_val = (uintptr_t)start;
    uintptr_t end_val = (uintptr_t)end;

    return ptr_val >= start_val && ptr_val < end_val;
}

void add_page(page_t **head, page_t *new_page)
{
    fprintf(stderr, "add_page\n");
    assert(new_page != NULL);
    if (new_page == NULL) return;

    new_page->next = *head;
    *head = new_page;
}

void free_block_in_page(page_t *page, void *ptr)
{
    fprintf(stderr, "free_block_in_page\n");
    if (page == NULL || ptr == NULL) return;

    if (!is_block_in_page(page, ptr)) {
        assert(0);
        return;
    }

    add_block_to_page_free_list(page, ptr);

    // Update the metadata
    size_t block_index = ((char *)ptr - page->blocks) / page->object_size;
    page->metadata[block_index].is_free = 1;

    // Update the block counts
    page->free_block_count++;
}

page_t *find_page_with_free_block(page_t *head, size_t object_size)
{
    fprintf(stderr, "find_page_with_free_block\n");
    page_t *current_page = head;
    while (current_page != NULL)
    {
        if (current_page->object_size == object_size)
        {
            if (current_page->free_block_count > 0)
            {
                return current_page;
            }
        }
        current_page = current_page->next;
    }

    return NULL;
}

/***********************************************************************************

   Author: Dylan Mumm
   Student ID: C18070517

   Professor Name: Jacob Sorber
   Semester: Fall 2023
   Class ID: CPSC 3220
   Class Title: Operating Systems
   Section ID: 001

   Project Name:  Project #3: MemoryAllocator

***********************************************************************************/

#include "allocator.h"

static allocator_state_t global_state;

static int initialized = 0;

__attribute__((constructor)) void shim_init()
{
    static int initializing = 0;
    assert(initializing == 0);
    if (initializing) {
        fprintf(stderr, "Tried to shim_init() while initializing");
        exit(EXIT_FAILURE);
    }

    initializing = 1;
    allocator_init(&global_state);

    initialized  = 1;
    initializing = 0;
    fprintf(stderr,"Shim Init!\n");
}

__attribute__((destructor)) void shim_destroy()
{
    fprintf(stderr,"Shim Done!\n");
}

// Helper function to determine the size class index based on the requested size
// Arguments:
//   - size: The size of the object to allocate
// Returns:
//   - The index of the size class to use
static size_t get_size_class(size_t size)
{
    fprintf(stderr,"Get Size Class!\n");
    assert(size != 0);
    if (size == 0) return 0; // Handle zero size as a special case

    size_t power = 1; // Start with power of 2 = 2^0 => 1
    size_t class_index = 0;

    // Find the smallest power of two greater than or equal to size
    while (power < size) {
        power <<= 1; // Multiply power by 2 via left shift
        class_index++; // Track power of two
    }

    assert(class_index > 0 && class_index < NUM_SIZE_CLASSES);
    return class_index;
}

// Initialize the allocator
void allocator_init(allocator_state_t *state)
{
    fprintf(stderr,"Allocator Init!\n");
    assert(state != NULL);
    if (state == NULL) return;

    // Initialize empty page lists for each size class
    for (int i = 0; i < NUM_SIZE_CLASSES; i++) {
        global_state.page_lists[i].head = NULL;
    }

    // Initialize the large object tracker
    init_large_object_tracker(&state->large_object_tracker);
}

// Clean up the allocator
void allocator_destroy(allocator_state_t *state)
{
    fprintf(stderr,"Allocator Destroy!\n");
    assert(state != NULL);
    if (state == NULL) return;

    // Iterate over each size class and release all pages
    for (int i = 0; i < NUM_SIZE_CLASSES; i++)
    {
        page_t *current_page = state->page_lists[i].head;
        while (current_page != NULL)
        {
            page_t *next_page = current_page->next;
            size_t total_size = current_page->block_count * current_page->object_size; // TODO: check this math especially sizeof
            munmap(current_page, total_size);
            current_page = next_page;
        }
    }

    // large objects are tracked with mmap and need to be unmapped
    large_object_record_t *current_record = state->large_object_tracker.head;
    while (current_record != NULL)
    {
        void *actual_address = (char *)current_record - sizeof(large_object_record_t);
        munmap(actual_address, current_record->size + sizeof(large_object_record_t));
        current_record = current_record->next;
    }

}

// Allocate memory
void *malloc(size_t size)
{

    fprintf(stderr,"Malloc!\n");

    if (size == 0) return NULL;

    void *block;
    if (size > 1024) // Allocate large object
    {
        fprintf(stderr,"Large Object!\n");
        block = mmap(NULL, size + sizeof(large_object_record_t),
                     PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
                      -1, 0);

        assert(block != MAP_FAILED);
        if (block == MAP_FAILED) return NULL;

        track_large_allocation(&global_state.large_object_tracker, block, size);
        return (char *)block + sizeof(large_object_record_t);  // Adjust pointer to account for tracking record
    }
    else // Allocate small object
    {
        fprintf(stderr,"Small Object!\n");
        size_t size_class = get_size_class(size);
        assert(size_class < NUM_SIZE_CLASSES);

        page_t *page = find_page_with_free_block(global_state.page_lists[size_class].head, size);
        if (!page) // No page found with free block
        {
            page = create_page(size_class);

            assert(page != NULL);
            if (!page) return NULL; // Failed to create a new page

            add_page(&global_state.page_lists[size_class].head, page);
        }

        // Find the first free block using metadata
        for (size_t i = 0; i < page->block_count; ++i)
        {
            if (page->metadata[i].is_free)
            {
                page->metadata[i].is_free = 0; // Mark block as used
                block = page->blocks + (i * page->object_size); // Calculate the address of the block
                page->free_block_count--; // Decrement the free block count
                break; // Stop searching
            }
        }
    }
    assert(0); // Should never reach this point
    return NULL; // Add this as a default return statement.

}

// Free memory
void free(void *ptr)
{
    fprintf(stderr,"Free!\n");
    if (ptr == NULL) return;

    // Determine if the block is a large allocation
    if (is_large_allocation_tracked(&global_state.large_object_tracker, ptr))
    {
        void *actual_block = (char *)ptr - sizeof(large_object_record_t);
        untrack_large_allocation(&global_state.large_object_tracker, actual_block);
        munmap(actual_block, /*TODO: find size*/ 0);  // Size needs to be known or stored somewhere
    }
    else
    {
        // Determine the size class from the block size
        size_t block_size = get_block_size(ptr);
        size_t size_class = get_size_class(block_size);

        // Scan the pages in the size class to find the correct page
        page_t *current_page = global_state.page_lists[size_class].head;
        while (current_page != NULL)
        {
            if (is_block_in_page(current_page, ptr))
            {
                free_block_in_page(current_page, ptr);
                return;
            }
            current_page = current_page->next;
        }
    }
    // The block was not found in any page
    assert(0);
}

// Allocate zero-initialized memory
void *calloc(size_t nmemb, size_t size)
{
    fprintf(stderr,"Calloc!\n");
    assert(nmemb != 0 && size != 0);
    if (nmemb == 0 || size == 0) return NULL;

    // Calculate total size to allocate
    size_t total_size = nmemb * size;

    // Check for overflow in the multiplication
    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL; // Multiplication overflowed
    }

    void *block = malloc(total_size);

    assert (block != NULL);
    if (! block) return NULL;

    // Zero out the allocated memory
    memset(block, 0, total_size);

    return block;
}

// Resize allocated memory
void *realloc(void *ptr, size_t size)
{
    fprintf(stderr,"Realloc!\n");

    // call is equivalent to malloc(size)
    assert(ptr != NULL);
    if (!ptr) return malloc(size);

    // call is equivalent to free(ptr)
    assert(size != 0);
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    //TODO: fix this
    size_t current_size = get_block_size(ptr);

    void *new_ptr = malloc(size);
    if (!new_ptr) return NULL;

    // Copy the contents from the old block to the new block
    // The amount of data to copy is the smaller of the new and the old sizes
    if(current_size < size)
    {
        memcpy(new_ptr, ptr, current_size);
    }
    else
    {
        memcpy(new_ptr, ptr, size);
    }

    free(ptr);

    return new_ptr;
}


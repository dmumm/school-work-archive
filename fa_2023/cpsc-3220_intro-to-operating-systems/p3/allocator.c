#include "allocator.h"

page_t* smallObjectClassLists[10];

void __attribute__ ((constructor)) shim_init()
{
    for(int i = 0; i < 10; i++)
    {
        smallObjectClassLists[i] = NULL;
    }
}

void __attribute__ ((destructor)) shim_destroy()
{
    for(int i = 0; i < 10; i++)
    {
        page_t* i_page = smallObjectClassLists[i];
        if (i_page == NULL) continue;

        munmap(i_page, PAGESIZE);
    }
}

/**
 * @brief Helper function to determine the size class index based on the requested size:
 * @param size The size of the object to allocate
 * @return size_t The index of the size class to use, 1-indexed. 0 if size is 0.
 */
static size_t get_size_class(size_t size)
{
    if (size == 0) return 0; // Handle zero size as a special case

    size_t power = 1;
    size_t exponent = 0;

    // Find the smallest power of two greater than or equal to size
    while (power < size)
    {
        power <<= 1; // Multiply power by 2 via left shift
        exponent++; // Track power of two
    }

    /*
    size 0 -> exponent 0 (null)
    size 1 -> exponent 1 (0)
    size 2 -> exponent 1 (0)
    size 3 -> exponent 2 (1)
    size 4 -> exponent 2 (1)
    size 8 -> exponent 3 (2)
    size 16 -> exponent 4 (3)
    size 32 -> exponent 5 (4)
    size 64 -> exponent 6 (5)
    size 128 -> exponent 7 (6)
    size 256 -> exponent 8 (7)
    size 512 -> exponent 9 (8)
    size 1024 -> exponent 10 (9)
    size 1025 -> exponent 11 (10)
    */
    // assert(exponent >= 0 && exponent <= NUM_SIZE_CLASSES);
    return exponent;
}


void* my_malloc(size_t size)
{

    if (size == 0) return NULL; // Handle zero size as a special case

    size_t size_index = get_size_class(size) - 1; // Change to 0-indexed
    if (size_index < 0) return NULL;

    if (size_index >= 10)
    {
        size_t total_size = sizeof(metadata_t) + size;
        void* result = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (result == MAP_FAILED) return NULL;

        metadata_t* metadata = (metadata_t*)result;
        metadata->size = total_size;
        metadata->identifier = LARGE_OBJECT_IDENTIFIER;

        return (void*)((uint8_t*)result + sizeof(metadata_t));
    }

    // For small objects, find or create a suitable page
    page_t* page = smallObjectClassLists[size_index];
    while (page != NULL && page->free_list == NULL)
    {
        page = page->next;
    }

    if (page == NULL) // Need to create a new page
    {
        page = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (page == MAP_FAILED) return NULL;

        page->block_size = pow(2, size_index + 1);
        page->next = smallObjectClassLists[size_index];
        smallObjectClassLists[size_index] = page;

        // Initialize blocks in the new page
        uint8_t* block_ptr = (uint8_t*)page + sizeof(page_t);
        size_t available_space = PAGESIZE - sizeof(page_t);
        size_t block_total_size = sizeof(block_t) + page->block_size;

        page->free_list = (block_t*)block_ptr;
        block_t* block = page->free_list;
        block->page = page;

        while (available_space >= block_total_size)
        {
            block_ptr += block_total_size;
            available_space -= block_total_size;

            if (available_space >= block_total_size)
            {
                block->next = (block_t*)block_ptr;
                block = block->next;
            }
            else
            {
                block->next = NULL;
            }
        }
    }

    // Allocate the first block from the free list
    block_t* allocated_block = page->free_list;
    page->free_list = allocated_block->next;
    return (void*)((uint8_t*)allocated_block + sizeof(block_t));
}



void my_free(void* ptr)
{
    if (ptr == NULL) return;

    metadata_t* metadata = (metadata_t*)((uint8_t*)ptr - sizeof(metadata_t));

    if (metadata->identifier == LARGE_OBJECT_IDENTIFIER)
    {
        munmap((void*)metadata, metadata->size);
    }
    else
    {
        block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
        page_t* page = block->page;
        if (page == NULL) return;

        block->next = page->free_list;
        page->free_list = block;
    }
}

void* my_realloc(void* ptr, size_t size)
{
    if (ptr == NULL) return my_malloc(size);
    if (size == 0)
    {
        my_free(ptr);
        return NULL;
    }

    metadata_t* metadata = (metadata_t*)((uint8_t*)ptr - sizeof(metadata_t));
    size_t original_size;

    if (metadata->identifier == LARGE_OBJECT_IDENTIFIER)
    {
        original_size = metadata->size - sizeof(metadata_t);
        if (size <= original_size) {
            return ptr; // The new size fits within the original large object allocation
        }
    }
    else
    {
        block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
        original_size = block->page->block_size;

        size_t original_size_class = get_size_class(original_size) - 1;
        size_t new_size_class = get_size_class(size) - 1;

        if (new_size_class == original_size_class) {
            return ptr; // The new size fits within the original small object size class
        }
    }

    void* new_ptr = my_malloc(size);
    if (new_ptr != NULL) {
        memcpy(new_ptr, ptr, original_size < size ? original_size : size);
        my_free(ptr);
    }
    return new_ptr;
}


void* my_calloc(size_t nitems, size_t size)
{
    size_t total_size = nitems * size;
    if (nitems != 0 && total_size / nitems != size) return NULL; // overflow

    void* ptr = my_malloc(size);

    if (ptr != NULL)
    {
        memset(ptr, 0, total_size);
    }

    return ptr;
}
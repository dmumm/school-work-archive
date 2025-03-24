#include "allocator.h"

page_t* smallObjectFreeLists[10];

void __attribute__ ((constructor)) shim_init()
{
    for(int i = 0; i < 10; i++)
    {
        smallObjectFreeLists[i] = NULL;
    }
}

void __attribute__ ((destructor)) shim_destroy()
{
    for(int i = 0; i < 10; i++)
    {
        page_t* i_page = smallObjectFreeLists[i];
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
    while (power < size) {
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
    size_t size_index = get_size_class(size) - 1; // change to 0-indexed
    if(size_index < 0) return NULL;

    // Large objects, ie >2^10 bytes, ie more than 1024 bytes
    // get a dedicated page for the object
    if(size_index > 10)
    {
        void* result = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if(result == MAP_FAILED) return NULL;

        return result;
    }

    // assert(size_index >= 0 && size_index <= 10);
    // -- Small objects, ie <=2^10 bytes, ie 1024 bytes or less -- //
    // Look for a page with free blocks in smallObjectFreeLists
    page_t* currentPage = smallObjectFreeLists[size_index];
    while (currentPage != NULL) //
    {
        block_t* block = currentPage->data;
        if (block != NULL) // there's a free block in the current page
        {
            currentPage->data = block->next; // Update the head of the free list
            return block->data; // Return the address of the allocated block
        }
        currentPage = currentPage->next;
    }

    // Create a new page if no free block was found
    page_t* newPage = mmap(NULL, PAGESIZE + sizeof(page_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(newPage == MAP_FAILED) return NULL;

    newPage->size = (int) pow(2, size_index + 1);
    newPage->next = smallObjectFreeLists[size_index]; // Add the new page at the beginning of the list
    smallObjectFreeLists[size_index] = newPage;

    // Initialize blocks in the new page
    char* blockStart = (char*)newPage + sizeof(page_t);
    for(int i = 0; i < (PAGESIZE / newPage->size); i++)
    {
        block_t* newBlock = (block_t*)(blockStart + i * newPage->size);
        newBlock->size = newPage->size;
        newBlock->data = (void*)((char*)newBlock + sizeof(block_t));
        if (i < (PAGESIZE / newPage->size) - 1)
        {
            newBlock->next = (block_t*)(blockStart + (i + 1) * newPage->size);
        }
        else
        {
            newBlock->next = NULL;
        }
    }

    newPage->data = (void*) (blockStart + sizeof(block_t)); // First block in the new page
    return newPage->data; // Return the address of the first block
}

void my_free(void* ptr)
{
    // check if ptr is in a page
    int in_page = 0;
    for(int i = 0; i < 10; i++)
    {
        if(smallObjectFreeLists[i] == NULL) continue;

        // get the page ptr is in
        page_t* pageIterator = smallObjectFreeLists[i];
        while(pageIterator != NULL)
        {
            if((char*) ptr >= (char*) pageIterator
            && (char*) ptr < (char*) pageIterator + PAGESIZE)
            {
                in_page = 1;
                break; // end while
            }
            pageIterator = pageIterator->next;
        }
        page_t* thisPage = pageIterator;

        if (in_page == 0) continue;
        // assert(in_page == 1);

        int block_size = (int) pow(2, i + 1);

        // get block index from pointer arithmetic
        int block_index = ((intptr_t) ptr - (intptr_t) smallObjectFreeLists[i]->data) / block_size;

        block_t* freeBlock = smallObjectFreeLists[i]->data + (block_index * block_size);

        // add block to front of free list
        freeBlock->next = smallObjectFreeLists[i]->data;
        smallObjectFreeLists[i]->data = freeBlock;

        //-- check if page is completely free --//

        int non_free_in_page_i = 0;
        for(int j = 0; j < smallObjectFreeLists[i]->size / block_size; j++)
        {
            block_t* block_j = smallObjectFreeLists[i]->data + (j * block_size);
            if(block_j->next != NULL)
            {
                non_free_in_page_i++;
                return; // page not free and can't be freed
            }
        }

        // if (non_free_in_page_i > 0) continue;
        // assert(non_free_in_page_i == 0);

        //-- freeing page of all free blocks --//

        // if given page is the only page in the free list
        if(smallObjectFreeLists[i]->next == NULL)
        {
            munmap(smallObjectFreeLists[i], PAGESIZE + sizeof(page_t));
            smallObjectFreeLists[i] = NULL;
            return;
        }

        //-- else if given page is not the only page in the free list --//
        // get page before this page, set its next to NULL, and free this page

        pageIterator = smallObjectFreeLists[i];
        while(pageIterator->next != thisPage && pageIterator != thisPage)
        {
            pageIterator = pageIterator->next;
        }
        page_t* prevPage = pageIterator;

        prevPage->next = NULL;
        munmap(thisPage, PAGESIZE + sizeof(page_t));
        return;
    }

    // if ptr is not in a page:
    // assert(in_page == 0);

    // figure out size of allocated memory using pointer arithmetic //TODO: make this more legible, elaborate
    int size = (int) pow(2, (int) log2((intptr_t) ptr) + 1);

    // round up to next power of 2
    int roundedSize = 1;
    while(roundedSize < size) {
        roundedSize *= 2;
    }

    // free chunk
    munmap(ptr, roundedSize);

}

void* my_realloc(void* ptr, size_t size)
{
    my_free(ptr);
    return my_malloc(size);
}

void* my_calloc(size_t nitems, size_t size)
{
    size_t total_size = nitems * size;
    if (nitems != 0 && total_size / nitems != size) return NULL; // overflow

    void* ptr = my_malloc(size);

    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }

    return ptr;
}
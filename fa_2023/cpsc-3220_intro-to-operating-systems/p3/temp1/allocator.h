#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <fcntl.h>
#include <stddef.h>
#include <sys/mman.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>

#define PAGESIZE 4096
#define NUM_SIZE_CLASSES 10
// Number of size classes (2, 4, 8, ..., 1024)

typedef struct block {
    void* data;
    size_t size;
    size_t is_free; // Indicates if the block is free
    struct block* next;
} block_t;

typedef struct page {
    block_t* data; // Pointer to the first block in the page
    size_t size; // Size of each block in the page
    size_t has_free_blocks; // Indicates if the page contains any free blocks
    struct page* next;
} page_t;

void __attribute__ ((constructor)) shim_init();
void __attribute__ ((destructor)) shim_destroy();

/**
 * @brief Allocates memory
 * @param size Number of bytes to allocate
 * @return void* A pointer to the allocated memory, or NULL if allocation failed
 */
void* my_malloc(size_t size);

/**
 * @brief Free memory
 * @param ptr Pointer to the memory to free
 */
void my_free(void* ptr);

/**
 * @brief Allocate zero-initialized memory
 * @param nitems Number of elements to allocate.
 * @param size Number of bytes to allocate.
 * @return void* Pointer to the allocated memory.
 */
void* my_calloc(size_t nitems, size_t size);

/**
 * @brief Reallocate memory
 * @param ptr Pointer to the memory to reallocate
 * @param size New size of the allocation
 * @return void* A pointer to the reallocated memory, or NULL if reallocation failed
 */
void* my_realloc(void* ptr, size_t size);

#endif // ALLOCATOR_H
#ifndef MYALLOC_H
#define MYALLOC_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include "allocator.h"

/**
 * @brief Allocates memory
 * @param size Number of bytes to allocate
 * @return void* A pointer to the allocated memory, or NULL if allocation failed
 */
__attribute__((visibility("default")))
void* malloc(size_t size);

/**
 * @brief Free memory
 * @param ptr Pointer to the memory to free
 */
__attribute__((visibility("default")))
void free(void* ptr);

/**
 * @brief Allocate zero-initialized memory
 * @param nitems Number of elements to allocate.
 * @param size Number of bytes to allocate.
 * @return void* Pointer to the allocated memory.
 */
__attribute__((visibility("default")))
void* calloc(size_t nitems, size_t size);

/**
 * @brief Reallocate memory
 * @param ptr Pointer to the memory to reallocate
 * @param size New size of the allocation
 * @return void* A pointer to the reallocated memory, or NULL if reallocation failed
 */
__attribute__((visibility("default")))
void* realloc(void* ptr, size_t size);

#endif // MYALLOC_H
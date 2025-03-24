#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#ifndef PAGE_H
#define PAGE_H

#include <stddef.h>
#include <unistd.h>    // For sysconf
#include <sys/mman.h>  // For mmap and munmap
#include <stdint.h>    // For uintptr_t
#include <stdio.h> // For fprintf

#include "free_list.h"  // Include the free list header

 #define PAGESIZE 4096


// Page structure definition
typedef struct block_metadata {
    int is_free;  // Flag indicating if the block is free
} block_metadata_t;

typedef struct page {
    size_t object_size;             // Size of objects managed by this page
    size_t block_count;             // Total number of blocks in this page
    size_t free_block_count;        // Number of free blocks available
    free_list_node_t *free_list;    // Pointer to the head of the free list
    struct page *next;              // Pointer to the next page
    block_metadata_t *metadata;     // Array of metadata for each block
    char *blocks;                   // Pointer to the start of the blocks
} page_t;

typedef struct page_list {
    page_t *head;
} page_list_t;

// Function to create a new page for a specific object size
// Arguments:
//   - object_size: The size of objects that the page will manage
// Returns:
//   - A pointer to the newly created page
page_t *create_page(size_t object_size);

// Function to add a page to a page list
// Arguments:
//   - head: Pointer to the head of the page list
//   - new_page: Page to be added to the list
void add_page(page_t **head, page_t *new_page);

// Function to find a page in the list that has a free block of the required size
// Arguments:
//   - head: Pointer to the head of the page list
//   - object_size: The size of the object to allocate
// Returns:
//   - A pointer to a suitable page, or NULL if none found
page_t *find_page_with_free_block(page_t *head, size_t object_size);

// Function to remove a page from the page list
// Note: Does not deallocate the page's memory; it simply removes it from the list
// Arguments:
//   - head: Pointer to the head of the page list
//   - page: Page to be removed from the list
void remove_page(page_t **head, page_t *page);

// Optional: Function to free a page
// Arguments:
//   - page: Page to be freed
void free_page(page_t *page);

// Function to remove a block from the page's free list
// Arguments:
//   - page: The page from which the block is to be removed
// Returns:
//   - Pointer to the block removed from the free list, or NULL if the list is empty
void *remove_block_from_page_free_list(page_t *page);

// Function to check if a page is full (i.e., has no free blocks)
// Arguments:
//   - page: The page to be checked
// Returns:
//   - Non-zero if the page is full, 0 otherwise
int is_page_full(const page_t *page);

// Function to get the size of a block
// Arguments:
//   - ptr: The pointer to the block
// Returns:
//   - The size of the block
size_t get_block_size(void *ptr);

// Bool to check if a pointer is in a page
// Arguments:
//   - page: The page to check
//   - ptr: The pointer to check
// Returns:
//   - Non-zero if the pointer is in the page, 0 otherwise
int is_block_in_page(page_t *page, void *ptr);

// Function to free a block in a page
// Arguments:
//   - page: The page to free the block in
//   - ptr: The pointer to the block to free
void free_block_in_page(page_t *page, void *ptr);

#endif // PAGE_H

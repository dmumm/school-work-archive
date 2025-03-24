#ifndef FREE_LIST_H
#define FREE_LIST_H

#include <assert.h>  // For assert

// #include <stdlib.h>  // Standard library for basic functions
// #include <sys/mman.h>  // For memory mapping (mmap, munmap)
// #include <fcntl.h>  // For file control options
// #include <string.h>  // For string manipulation functions
// #include <stddef.h>  // For size_t

typedef struct free_list_node {
    struct free_list_node *next;  // Pointer to the next node in the list
} free_list_node_t;

// Include page.h after the definition of free_list_node_t
#include "page.h"


// Function to add a node to the free list
// Arguments:
//   - head: Pointer to the head of the free list
//   - node: Node to be added to the free list
void add_to_free_list(free_list_node_t **head, free_list_node_t *node);


// Function to remove a node from the free list
// Arguments:
//   - head: Pointer to the head of the free list
//   - node: Node to be removed from the free list
void remove_from_free_list(free_list_node_t **head, free_list_node_t *node);


// Function to find a suitable node in the free list
// Arguments:
//   - head: Pointer to the head of the free list
// Returns:
//   - Pointer to a suitable free list node, or NULL if none found
free_list_node_t *find_suitable_node(free_list_node_t *head);

#endif // FREE_LIST_H


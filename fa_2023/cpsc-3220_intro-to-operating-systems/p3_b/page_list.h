#ifndef PAGE_LIST_H
#define PAGE_LIST_H

#include "page.h"

typedef struct page_list_node {
    page_t *page;
    struct page_list_node *next;
} page_list_node_t;

//----// Function declarations for page list operations //----//

// Create a new page list node with the given page
page_list_node_t *create_page_list_node(page_t *page);

// Add a page to the beginning of a page list
void add_page_to_list(page_list_node_t **head, page_t *page);

// Find a page in the list that meets certain criteria (e.g., has free space)
page_t *find_page_in_list(page_list_node_t *head, size_t size);

// Remove a page from the list
void remove_page_from_list(page_list_node_t **head, page_t *page);

// Optional: Functions to free the list, print the list for debugging, etc.

#endif // PAGE_LIST_H
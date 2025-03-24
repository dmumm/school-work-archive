#include "page_list.h"

// Assuming there's a custom function to allocate memory from the allocator's pool
extern void *allocator_alloc(size_t size);

// Create a new page list node with the given page
page_list_node_t *create_page_list_node(page_t *page) {
    page_list_node_t *node = (page_list_node_t *)allocator_alloc(sizeof(page_list_node_t));
    if (node == NULL) {
        return NULL; // Allocation failed
    }

    node->page = page;
    node->next = NULL;
    return node;
}

// Add a page to the beginning of a page list
void add_page_to_list(page_list_node_t **head, page_t *page) {
    page_list_node_t *new_node = create_page_list_node(page);
    if (new_node == NULL) {
        // Handle allocation failure if necessary
        return;
    }

    new_node->next = *head;
    *head = new_node;
}

// Find a page in the list that meets certain criteria
page_t *find_page_in_list(page_list_node_t *head, size_t size) {
    page_list_node_t *current = head;
    while (current != NULL) {
        if (current->page->object_size == size) { // TODO: check for additional pages
            return current->page;
        }
        current = current->next;
    }
    return NULL;
}

// Remove a page from the list
void remove_page_from_list(page_list_node_t **head, page_t *page) {
    if (head == NULL || *head == NULL) {
        return; // List is empty or head is null
    }

    page_list_node_t *current = *head, *prev = NULL;
    while (current != NULL) {
        if (current->page == page) {
            if (prev == NULL) {
                *head = current->next; // Remove the first node
            } else {
                prev->next = current->next; // Remove a middle or last node
            }
            // Optionally free the node if your allocator supports it
            return;
        }
        prev = current;
        current = current->next;
    }
}
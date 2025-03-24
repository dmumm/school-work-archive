#include "free_list.h"

// Adds a specified node to the free list
void add_to_free_list(free_list_node_t **head, free_list_node_t *node)
{
    fprintf(stderr, "add_to_free_list\n");
    assert(node != NULL);

    if (node == NULL) return;

    // Insert the node at the beginning of the free list
    node->next = *head;
    *head = node;
}

// Removes a specified node from the free list
void remove_from_free_list(free_list_node_t **head, free_list_node_t *node)
{
    fprintf(stderr, "remove_from_free_list\n");
    if (head == NULL || *head == NULL || node == NULL) return;

    // Special case for head
    if (*head == node)
    {
        *head = node->next;
        return;
    }

    // Iterate through the list to find and remove the node
    free_list_node_t *current = *head;
    while (current->next != NULL && current->next != node)
    {
        current = current->next;
    }

    if (current->next == node)
    {
        current->next = node->next;
    }
}

// Finds a suitable node in the free list
// For simplicity, this function just returns the first node
// TODO: Replace this with a more sophisticated algorithm
free_list_node_t *find_suitable_node(free_list_node_t *head) {
    fprintf(stderr, "find_suitable_node\n");
    return head;
}
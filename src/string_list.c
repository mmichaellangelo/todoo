#include "string_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Adds a string element to the end of a linked list,
 * or initializes the head of the list.
 * @param head head of linked list
 * @param str string to add
 */
void list_add(node_t **head, const char *str) {
    // Create new node
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = strdup(str);
    new_node->next = NULL;
    // If head is empty, initialize it with the new string
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    // Otherwise, loop through until find first null
    node_t *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

/**
 * Prints a linked list with a specified style or does nothing
 * if the list is empty.
 * @param head first element of the list to print
 * @param style dashed or numbered
 */
void list_print(const node_t *head, const enum list_style style) {
    if (head == NULL) {
        return;
    }
    const node_t *current = head;
    int idx = 0;
    while (current != NULL) {
        switch (style) {
            case DASHED: // Dashed list
                printf("- %s\n", current->data);
                break;
            case NUMBERED: // Numbered list
                printf("[%d] %s\n", idx, current->data);
                break;
            default: // No prefix
                printf("%s\n", current->data);
                break;
        }
        current = current->next;
        idx++;
    }
}

/**
 * Removes an element from the list given its index
 * @param list list to remove from
 * @param idx index of element to remove
 * @return removed string or nullptr
 */
char* list_remove(node_t **list, const int idx) {
    // Check that list and head are not null and that index is non-negative
    if (list == NULL || *list == NULL || idx < 0) {
        return NULL;
    }
    // Case 1: remove head
    if (idx == 0) {
        node_t *node_to_free = *list;
        char* removed_data = node_to_free->data;
        *list = node_to_free->next;
        free(node_to_free);
        return removed_data;
    }
    // Case 2: remove middle or last
    node_t *current = *list;
    for (int i = 0; i < idx - 1; i++) {
        if (current->next == NULL) {
            return NULL;
        }
        current = current->next;
    }
    if (current->next == NULL) {
        return NULL;
    }
    node_t *node_to_free = current->next;
    char* removed_data = node_to_free->data;
    current->next = node_to_free->next;
    free(node_to_free);
    return removed_data;
}

int list_length(const node_t *list) {
    if (list == NULL) {
        return 0;
    }
    const node_t *current = list;
    int size = 0;
    while (current != NULL) {
        current = current ->next;
        size++;
    }
    return size;
}

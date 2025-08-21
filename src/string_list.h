#ifndef LIST_H
#define LIST_H

/** A node has string data and a pointer to the next node */
typedef struct node {
    char* data;
    struct node* next;
} node_t;

/** Style in which to print a list */
enum list_style {
    NUMBERED,
    DASHED
};

/**
 * Adds an element to the end of a list
 * @param head first element of list to add to
 * @param str data to add to list
 */
void list_add(node_t **head, const char *str);

/**
 * Removes an element from a list at a specified index
 * @param list first element of list to remove from
 * @param idx index of element to remove
 * @return removed string or nullptr
 */
char* list_remove(node_t **list, int idx);

/**
 * Prints the contents of a list, styled with dashes or indices
 * @param head first element of list to print
 * @param style 0 for dashes, 1 for numbers
 */
void list_print(const node_t *head, enum list_style style);


#endif //LIST_H

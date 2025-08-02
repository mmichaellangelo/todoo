#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Linked list for string */
typedef struct node {
    char* data;
    struct node* next;
} node_t;

/** M/D/YYYY current date */
char date[11];
/** Head of uncompleted todos list */
node_t *uncompleted_head = nullptr;
/** Head of completed todos list */
node_t *completed_head = nullptr;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Gets the current date as a M/D/YYYY string
 * @return today's date as M/D/YYYY string
 */
char* get_date_string() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, sizeof(date), "%d/%d/%d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
    return date;
}

/**
 * Prints commands
 */
void print_commands() {
    printf("[a] add, [c] complete, [q] quit\n");
}

/**
 * Prints the application header with today's date
 * @param tm timer for date
 */
void print_header() {
    printf("-- ToDoo %s --\n", get_date_string());
}

void print_uncompleted() {
    if (uncompleted_head == NULL) {
        return;
    }
    node_t *current = uncompleted_head;
    int idx = 0;
    while (current != NULL) {
        printf("[%d] %s\n", idx, current->data);
        current = current->next;
        idx++;
    }
}

void print_completed() {
    if (completed_head == NULL) {
        return;
    }
    node_t *current = completed_head;
    int idx = 0;
    while (current != NULL) {
        printf("[%d] %s\n", idx, current->data);
        current = current->next;
        idx++;
    }
}

void add_completed(char* str) {
    node_t *new_node = malloc(sizeof(node_t));
    strcpy(new_node->data, str);
    new_node->next = nullptr;
    if (completed_head == nullptr) {
        completed_head = new_node;
    } else {
        node_t *current = completed_head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void add_todo() {
    char todo[32];
    printf("Todo > ");
    fgets(todo, sizeof(todo), stdin);
    // Replace newline char with null terminator
    todo[strcspn(todo, "\n")] = 0;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = malloc(strlen(todo));
    strcpy(new_node->data, todo);
    if (uncompleted_head == nullptr) {
        uncompleted_head = new_node;
        new_node->next = nullptr;
    } else {
        node_t *current = uncompleted_head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = nullptr;
    }
}

void complete_todo() {
    if (uncompleted_head == nullptr) {
        printf("No todos in list\n");
        return;
    }
    printf("id > ");
    int id;
    scanf("%d", &id);
    clear_input_buffer();
    if (id < 0) {
        printf("Invalid id\n");
        return;
    }
    if (id == 0) {
        add_completed(uncompleted_head->data);
        uncompleted_head = uncompleted_head->next;
        return;
    }
    node_t *current = uncompleted_head;
    for (int i = 0; i < id; i++) {
        if (i == id - 1) {
            add_completed(current->next->data);
            current->next = current->next->next;
            return;
        }
        if (current->next == nullptr) {
            printf("Invalid id\n");
            return;
        }
        current = current->next;
    }
}

/**
 * Main loop
 * @return exit code
 */
int main() {
    for (;;) {
        system("clear");
        print_header();
        print_uncompleted();
        printf("-----------\n");
        print_completed();
        printf("-----------\n");
        print_commands();
        char input;
        printf("> ");
        input = getchar();
        clear_input_buffer();
        switch (input) {
            case 'a':
                add_todo();
                break;
            case 'c':
                complete_todo();
                break;
            case 'q':
                return 0;
            default:
                printf("Invalid command.\n");
        }
    }
}


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "string_list.h"

/** M/D/YYYY current date */
char date[11];
char *filepath;
/** Head of uncompleted todos list */
node_t *uncompleted = NULL;
/** Head of completed todos list */
node_t *completed = NULL;

/**
 * Gets the current date as an M/D/YYYY string
 * @return today's date as M/D/YYYY string
 */
char* get_date_string() {
    const time_t t = time(NULL);
    const struct tm tm = *localtime(&t);
    snprintf(date, sizeof(date), "%d/%d/%d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
    return date;
}

/**
 * Moves a todo from the uncompleted list to the completed list
 */
void complete(const int idx) {
    if (idx < 0 || uncompleted == NULL) {
        return;
    }
    const char *removed = list_remove(&uncompleted, idx);
    if (removed != NULL) {
        list_add(&completed, removed);
    }
}

/**
 * Handles a user command, whether it is adding a new todo,
 * completing one, or removing one.
 * @return 0 if program should exit
 */
int handle_command(char c[]) {
    c[strcspn(c, "\n")] = 0; // Trim newline character
    if (strlen(c) == 1 && c[0] == 'q') { // Handle program exit
        return 0;
    }
    char *endptr;
    long idx = strtol(c, &endptr, 10);
    if (endptr != c) { // Number was found
        while (*endptr && isspace((__u_char)*endptr)) endptr++; // Skip whitespace between idx and command
        if (*endptr == 'c') { // complete
            complete(idx);
        } else if (*endptr == 'r') { // remove
            list_remove(&uncompleted, idx);
        }
    } else {
        list_add(&uncompleted, c);
    }
    return 1;
}

/**
 * Saves todo list data to file
 * FORMAT: #*uncompleted1*uncompleted2...#*completed1*completed2...
 * @param path path to file to save
 */
void save_file(const char *path) {
    FILE *f = fopen(path, "w");
    fprintf(f, "#");
    node_t *current = uncompleted;
    while (current != NULL) {
        fprintf(f, "*%s", current->data);
        current = current->next;
    }
    fprintf(f, "#");
    current = completed;
    while (current != NULL) {
        fprintf(f, "*%s", current->data);
        current = current->next;
    }
    fclose(f);
}

/**
 * Loads todo list data from file
 * @param path path to file to load
 */
void load_file(char* path) {
    FILE *f = fopen(path, "r");
    char buf[100];
    fgets(buf, sizeof(buf), f);
    fclose(f);
    
}


/**
 * Main loop
 * @return exit code
 */
int main() {
    // load_file("todos.txt");
    for (;;) {
        system("clear"); // Clear screen
        printf("<< TODOO %s >>\n", get_date_string()); // Print header
        list_print(uncompleted, NUMBERED);
        
        if (completed != NULL) { // Print completed todos if there are any
            printf("--------------------\n");
            printf("#### COMPLETED: ####\n");
            list_print(completed, DASHED);
        }
        printf("--------------------\n");
        printf("[type] to add\n[idx][c] to complete\n[idx][r] to remove\n[q] to quit\n"); // List commands
        char input[64];
        printf("> ");
        fgets(input, sizeof(input), stdin);
        
        if (handle_command(input) == 0) {
            save_file("todos.txt");
            break;
        }
        save_file("todos.txt");
    }
    return 0;
}


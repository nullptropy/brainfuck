#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repl.h"
#include "linenoise.h"

static void repl_print_help() {
    printf("bfc:repl help\n"
           "    `pb or `print-buffer    print current `source` buffer\n"
           "    `q  or `quit            quit\n"
           "    `h  or `help            this text\n");
}

void repl() {
    char *buffer = malloc(sizeof(char) * 8);

    for (;;) {
        char *line = linenoise("::: ");

        if (line == NULL || line[0] == '\0') {
            free(line);
            continue;
        }

        if (line[0] != '`') {
            buffer = realloc(
                buffer, sizeof(char) * (strlen(buffer) + strlen(line)) + 1);
            strcat(buffer, line); free(line);
            continue;
        }

        // so dumb: strcmp(...) * strcmp(...)
        // todo: replace all of this with a `switch` that is
        // overkill x3
        if (strcmp(line, "`pb") * strcmp(line, "`print-buffer") == 0) {
            if (strlen(buffer) > 0) {
                printf("%s\n", buffer);
            }
        } 
        else if (strcmp(line, "`q") * strcmp(line, "`quit") == 0) {
            free(line);
            break;
        }
        else if (strcmp(line, "`h") * strcmp(line, "`help") == 0) {
            repl_print_help();
        }

        free(line);
    }

    free(buffer);
}
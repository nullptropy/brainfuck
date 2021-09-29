#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "compiler.h"
#include "vm.h"
#include "repl.h"
#include "opcode.h"
#include "linenoise.h"

#if defined(WIN32) || defined(_WIN32)
    #define PATH_SEPARATOR "\\"
#else
    #define PATH_SEPARATOR "/"
#endif

static void repl_print_help() {
    printf("repl help\n"
           "    `b  | `buffer          print current `source` buffer\n"
           "    `q  | `quit            quit\n"
           "    `r  | `run             interpret the `source` buffer\n"
           "    `h  | `help            print this text\n");
}

static void completion(const char *buffer, linenoiseCompletions *lc) {
    if (buffer[0] == '`')
        return;
}

void repl(int debug) {
    char *history_file_name = ".bfc_history";
    char *history_file_path = calloc(
        strlen(getenv("HOME")) + strlen(history_file_name) + 2, sizeof(char));

    strcpy(history_file_path, getenv("HOME"));
    strcat(history_file_path, PATH_SEPARATOR);
    strcat(history_file_path, history_file_name);

    linenoiseSetCompletionCallback(completion);
    linenoiseHistoryLoad(history_file_path);

    VM *vm = vm_new(30000);
    char *buffer = calloc(8, sizeof(char));

    for (;;) {
        char *line = linenoise("::: ");

        if (line == NULL || line[0] == '\0') {
            free(line);
            continue;
        }

        linenoiseHistoryAdd(line);
        linenoiseHistorySave(history_file_path);

        if (line[0] != '`') {
            buffer = realloc(
                buffer, sizeof(char) * (strlen(buffer) + strlen(line)) + 1);
            strcat(buffer, line);
            free(line); continue;
        }

        // lmao: strcmp(...) * strcmp(...)
        // todo: replace all of this with a `switch` statement that is probably overkill x3
        if (strcmp(line, "`b") * strcmp(line, "`buffer") == 0) {
            if (strlen(buffer) > 0)
                printf("%s\n", buffer);
        }
        else if (strcmp(line, "`q") * strcmp(line, "`quit") == 0) {
            free(line);
            break;
        }
        else if (strcmp(line, "`r") * strcmp(line, "`run") == 0) {
            OpCodeArray *program = compile(buffer);
            if (program != NULL) {
                vm_execute(vm, program, debug);
                array_free(program); free(program);
            }

            free(buffer); buffer = calloc(8, sizeof(char));
        }
        else if (strcmp(line, "`h") * strcmp(line, "`help") == 0) {
            repl_print_help();
        }

        free(line);
    }

    vm_free(vm);
    free(buffer);
    free(history_file_path);
}
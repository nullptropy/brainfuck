#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "repl.h"
#include "array.h"
#include "utils.h"
#include "opcode.h"
#include "compiler.h"

static void print_help_string() {
    printf("usage: ./bfc [path] [-d] [-h]\n"
           "\n"
           "optional arguments:\n"
           "    -d, --debug     run the interpreter in debug mode\n"
           "    -h, --help      print this text\n");
}

static void interpret_file(const char *path, int debug) {
    char *source = read_file(path);
    if (source == NULL)
        exit(1);

    OpCodeArray *program = compile(source);
    if (program == NULL) {
        free(source);
        exit(1);
    }

    VM *vm = vm_new(30000);
    vm_execute(vm, program, debug);

    vm_free(vm);
    free(source);
    array_free(program); free(program);
}

int main(int argc, char **argv) {
    int debug = 0;
    char *file_path = NULL;

    if (argc > 3) {
        print_help_string();
        return 0;
    }

    while (argc > 1) {
        argc--;
        argv++;

        if (strcmp(*argv, "-d") * strcmp(*argv, "--debug") == 0) {
            debug = 1;
        }
        else if (strcmp(*argv, "-h") * strcmp(*argv, "--help") == 0) {
            print_help_string();
            return 0;
        }
        else {
            file_path = *argv;
        }
    }

    if (file_path == NULL)
        repl(debug);
    else
        interpret_file(file_path, debug);

    return 0;
}
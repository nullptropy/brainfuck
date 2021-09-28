#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "repl.h"
#include "array.h"
#include "utils.h"
#include "opcode.h"
#include "compiler.h"

void run_file(const char *path) {
    char *source = read_file(path);
    if (source == NULL)
        exit(1);

    OpCodeArray program = compile(source);

    VM *vm = vm_new(30000);
    vm_execute(vm, &program);

    vm_free(vm);
    free(source);
    array_free(&program);
}

int main(int argc, char **argv) {
    switch (argc) {
        case 1: repl(); break;
        case 2: run_file(argv[1]); break;
        default:
            fprintf(stderr, "usage: %s [path]\n", argv[0]);
            break;
    }

    return 0;
}
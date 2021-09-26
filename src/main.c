#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "repl.h"
#include "array.h"
#include "opcode.h"
#include "compiler.h"

static char *read_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "failed to open file %s\n", path);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *buffer = (char*) malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "failed to allocate memory to read %s\n", path);
        exit(1);
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "failed to read the file %s\n", path);
        exit(1);
    }
    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}


void run_file(const char *path) {
    char *source = read_file(path);
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
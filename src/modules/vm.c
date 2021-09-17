#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "array.h"
#include "opcode.h"

VM *vm_new(int size) {
    VM *vm = (VM *) malloc(sizeof(VM));

    vm->ip = 0;
    vm->dp = 0;
    array_init(unsigned char, &vm->mem, size);

    return vm;
}

void vm_free(VM *vm) {
    array_free(&vm->mem);
    free(vm);
}

int vm_execute(VM *vm, OpCodeArray *program) {
    int exit_code = 0;

    #ifdef DEBUG
        array(char, buffer);
        array_init(char, &buffer, 8);
    #endif

    for (;;) {
        OpCode instruction = program->values[vm->ip];

        #ifdef DEBUG
            printf("%05d:%05d:0x%02x - ", vm->ip, vm->dp, vm->mem.values[vm->dp]);
            opcode_print(&instruction);
            printf("\n");
        #endif

        if (vm->dp >= vm->mem.cap || vm->ip >= program->num) {
            exit_code = 1;
            fprintf(stderr, "vm error: pointer overflow\n");
            goto exit_loop;
        }

        switch (instruction.type) {
            case OP_PCH:
                #ifdef DEBUG
                    array_add(&buffer, vm->mem.values[vm->dp]);
                #else
                    putchar(vm->mem.values[vm->dp]);
                #endif
                break;
            case OP_GCH:
                vm->mem.values[vm->dp] = getchar();
                break;
            case OP_ADD:
                vm->mem.values[vm->dp] += instruction.value;
                break;
            case OP_INC:
                vm->dp += instruction.value;
                break;
            case OP_JZE:
                vm->ip = vm->mem.values[vm->dp] == 0 ? instruction.value : vm->ip + 1;
                continue;
            case OP_JNZ:
                vm->ip = vm->mem.values[vm->dp] != 0 ? instruction.value : vm->ip + 1;
                continue;
            case OP_ZERO:
                vm->mem.values[vm->dp] = 0;
                break;
            case OP_HALT:
                goto exit_loop;
        }

        vm->ip++;
    }
    exit_loop:
        #ifdef DEBUG
            array_add(&buffer, '\0');
            printf("%s", buffer.values);
            array_free(&buffer);
        #endif

    return exit_code;
}
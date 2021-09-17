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
    for (;;) {
        OpCode instruction = program->values[vm->ip];

        switch (instruction.type) {
            case OP_PCH:
                putchar(vm->mem.values[vm->dp]);
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
                return 0;
        }

        vm->ip++;
    }
}
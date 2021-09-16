#include <stdio.h>
#include <string.h>

#include "array.h"
#include "opcode.h"

OpCodeArray compile(const char *source) {
    int index = 0;
    int error_occured = 0;

    array(int, stack); array_init(int, &stack, 8);
    array(OpCode, program); array_init(OpCode, &program, 8);

    while (index < strlen(source)) {
        char c = source[index];

        switch (c) {
            case '.': array_add(&program, opcode_new(OP_PCH, 0)); break;
            case ',': array_add(&program, opcode_new(OP_GCH, 0)); break;

            case '[': {
                array_add(&program, opcode_new(OP_JZE, -1));
                array_add(&stack, program.num);
                break;
            }
            case ']': {
                if (stack.num == 0) {
                    error_occured = 1;
                    fprintf(stderr, "compiler error: unmatched `]` at index %d\n",
                            index);
                    break;
                }

                int op_pos = array_pop(&stack) - 1;
                array_add(&program, opcode_new(OP_JNZ, op_pos + 1));
                program.values[op_pos].value = program.num;
                break;
            }

            case '+': case '-': case '>': case '<': {
                int value, repeats = 0; OpCodeType type;

                while (index < strlen(source)) {
                    if (strchr("+[>,.<]-", source[index]) != NULL) {
                        if (c != source[index]) {
                            break;
                        }
                        repeats++;
                    }
                    index++;
                }

                if (c == '+' || c == '>') { value = repeats; } else { value = -repeats; }
                if (c == '+' || c == '-') {  type = OP_ADD;  } else {  type = OP_INC;   }

                array_add(&program, opcode_new(type, value));
                continue;
            }
        }

        index++;
    }

    if (error_occured == 1 || stack.num != 0) {
        for (int i = 0; i < stack.num; i++) {
            fprintf(stderr, "compiler error: unmatched `[` at index %d\n",
                    stack.values[i]);
        }

        free((char*) source);
        array_free(&stack);
        array_free(&program);

        exit(1);
    }

    array_free(&stack);
    array_add(&program, opcode_new(OP_HALT, 0));

    return (OpCodeArray) {
        .values = program.values, .num = program.num, .cap = program.cap};
}
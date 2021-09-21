#include <stdio.h>
#include <string.h>

#include "array.h"
#include "opcode.h"

struct stack_entry {
    int file_index;
    int code_index;
};

OpCodeArray compile(const char *source) {
    int index = 0;
    int error_occured = 0;
    int file_length = strlen(source);

    array(OpCode, program);
    array(struct stack_entry, stack);

    array_init(OpCode, &program, 8);    
    array_init(struct stack_entry, &stack, 8);

    while (index < file_length) {
        char c = source[index];

        switch (c) {
            case '.': array_add(&program, opcode_new(OP_PCH, 0)); break;
            case ',': array_add(&program, opcode_new(OP_GCH, 0)); break;

            case '[': {
                if (source[index + 1] == '-' && source[index + 2] == ']') {
                    array_add(&program, opcode_new(OP_ZERO, 0));
                    index += 2;
                    break;
                }

                array_add(&program, opcode_new(OP_JZE, -1));
                array_add(&stack,
                        ((struct stack_entry){.file_index = index,
                                                .code_index = program.num}));
                break;
            }
            case ']': {
                if (stack.num == 0) {
                    error_occured = 1;
                    fprintf(stderr, "compiler error: unmatched `]` at index %d\n",
                            index);
                    break;
                }

                int opcode_index = array_pop(&stack).code_index - 1;
                array_add(&program, opcode_new(OP_JNZ, opcode_index + 1));
                program.values[opcode_index].value = program.num;
                break;
            }

            case '+': case '-': case '>': case '<': {
                int value, repeats = 0; OpCodeType type;

                while (index < file_length) {
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
                    stack.values[i].file_index);
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
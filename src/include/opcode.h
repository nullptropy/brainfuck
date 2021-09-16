#ifndef bf_opcode_h
#define bf_opcode_h

typedef enum {
    OP_PCH,
    OP_GCH,
    OP_ADD,
    OP_INC,
    OP_JZE,
    OP_JNZ,
    OP_HALT,
} OpCodeType;

typedef struct opcode {
    OpCodeType type;
    int value;
} OpCode;

typedef struct opcode_array {
    OpCode *values;
    int num;
    int cap;
} OpCodeArray;

OpCode opcode_new(OpCodeType type, int value);
void   opcode_print(OpCode *opcode);

#endif
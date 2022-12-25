#ifndef bf_opcode_h
#define bf_opcode_h

typedef enum {
    OP_PCH,
    OP_GCH,
    OP_ADD,
    OP_INC,
    OP_JZE,
    OP_JNZ,
    OP_ZERO,
    OP_HALT,
} OpcodeType;

typedef struct opcode {
    OpcodeType type;
    int value;
} Opcode;

typedef struct opcode_array {
    Opcode *values;
    int num;
    int cap;
} OpcodeArray;

Opcode opcode_new(OpcodeType type, int value);
void   opcode_print(Opcode *opcode);

#endif

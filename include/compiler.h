#ifndef bf_compiler_h
#define bf_compiler_h

#include <stdbool.h>

#include "array.h"
#include "opcode.h"

bool compile(const char *source, OpcodeArray *program);

#endif

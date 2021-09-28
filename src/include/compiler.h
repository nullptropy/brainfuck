#ifndef bf_compiler_h
#define bf_compiler_h

#include "array.h"
#include "opcode.h"

OpCodeArray *compile(const char *source);

#endif
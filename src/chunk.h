#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,

    OP_NEGATE,
    OP_NOT,

    OP_PRINT,

    OP_POP,

    OP_NIL,
    OP_TRUE,
    OP_FALSE,

    OP_DEFINE_GLOBAL,
    OP_GET_GLOBAL,
    OP_SET_GLOBAL,

    OP_GET_LOCAL,
    OP_SET_LOCAL,

    OP_EQUAL,
    OP_GREATER,
    OP_LESS,

    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
} OpCode;

typedef struct {
    i32 count;
    i32 capacity;
    byte* code;
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, byte byte, i32 line);
void freeChunk(Chunk* chunk);

i32 addConstant(Chunk* chunk, Value value);

#endif
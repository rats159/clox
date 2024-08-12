#include "chunk.h"
#include "memory.h"
#include <stdlib.h>

void initChunk(Chunk* chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, byte b, i32 line) {
    if (chunk->capacity < chunk->count + 1) {
        i32 old_cap = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_cap);
        chunk->code = GROW_ARRAY(byte, chunk->code, old_cap, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, old_cap, chunk->capacity);
    }

    chunk->code[chunk->count] = b;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(byte, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

i32 addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
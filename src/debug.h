#ifndef clox_debug_h
#define cloc_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
i32 disassembleInstruction(Chunk* chunk, i32 offset);

#endif
#ifndef clox_debug_h
#define cloc_debug_h

#include "chunk.h"

#define PRINT_STRUCT_BYTES(ptr, type)            \
    do {                                         \
        byte* byteptr = (byte*)(ptr);            \
        for (i32 i = 0; i < sizeof(type); i++) { \
            printf("%02x ", byteptr[i]);         \
        }                                        \
        printf("\n");                            \
    } while (0);

void disassembleChunk(Chunk* chunk, const char* name);
i32 disassembleInstruction(Chunk* chunk, i32 offset);

#endif
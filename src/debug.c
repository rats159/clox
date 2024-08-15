#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (i32 offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static i32 simpleInstruction(const char* name, i32 offset) {
    printf("%s\n", name);
    return offset + 1;
}

static i32 constantInstruction(const char* name, Chunk* chunk, i32 offset) {
    byte constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

i32 disassembleInstruction(Chunk* chunk, i32 offset) {
#define SIMPLE(token) \
    case token: return simpleInstruction(#token, offset)
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    byte instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);

            // I like this little macro, but clang-format does not.
            SIMPLE(OP_NIL);
            SIMPLE(OP_FALSE);
            SIMPLE(OP_TRUE);

            SIMPLE(OP_EQUAL);
            SIMPLE(OP_GREATER);
            SIMPLE(OP_LESS);

            SIMPLE(OP_NOT);
            SIMPLE(OP_NEGATE);

            SIMPLE(OP_RETURN);
            SIMPLE(OP_ADD);
            SIMPLE(OP_SUBTRACT);
            SIMPLE(OP_DIVIDE);
            SIMPLE(OP_MULTIPLY);
        default: printf("Unknown opcode %d\n", instruction); return offset + 1;
    }
#undef SIMPLE
}

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

static i32 byteInstruction(const char* name, Chunk* chunk, i32 offset) {
    byte slot = chunk->code[offset + 1];
    printf("%-16s %4d\n", name, slot);
    return offset + 2;
}

static i32 jumpInstruction(const char* name, i32 sign, Chunk* chunk,
                           i32 offset) {
    u16 jump = (u16)(chunk->code[offset + 1] << 8);
    jump |= chunk->code[offset + 2];
    printf("%-16s %4d -> %d\n", name, offset, offset + 3 + sign * jump);
    return offset + 3;
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

        case OP_DEFINE_GLOBAL:
            return constantInstruction("OP_DEFINE_GLOBAL", chunk, offset);

        case OP_GET_GLOBAL:
            return constantInstruction("OP_GET_GLOBAL", chunk, offset);

        case OP_SET_GLOBAL:
            return constantInstruction("OP_SET_GLOBAL", chunk, offset);

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

            SIMPLE(OP_POP);

            SIMPLE(OP_PRINT);

        case OP_GET_LOCAL:
            return byteInstruction("OP_GET_LOCAL", chunk, offset);
        case OP_SET_LOCAL:
            return byteInstruction("OP_SET_LOCAL", chunk, offset);

        case OP_LOOP: return jumpInstruction("OP_LOOP", -1, chunk, offset);
        case OP_JUMP: return jumpInstruction("OP_JUMP", 1, chunk, offset);
        case OP_JUMP_IF_FALSE:
            return jumpInstruction("OP_JUMP_IF_FALSE", 1, chunk, offset);
        default: printf("Unknown opcode %d\n", instruction); return offset + 1;
    }
#undef SIMPLE
}

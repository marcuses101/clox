#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "line.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initLines(&chunk->lines);
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code =
        GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  addLineNumberOccurence(&chunk->lines, line);
  chunk->count++;
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeLines(&chunk->lines);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);

  return chunk->constants.count - 1;
}

void writeConstant(Chunk *chunk, Value value, int line) {
  int constantIndex = addConstant(chunk, value);

  if (constantIndex < 256) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, constantIndex, line);
    return;
  }
  writeChunk(chunk, OP_CONSTANT_LONG, line);
  writeChunk(chunk, (constantIndex >> 16) & 0xFF, line);
  writeChunk(chunk, (constantIndex >> 8) & 0xFF, line);
  writeChunk(chunk, (constantIndex) & 0xFF, line);
}

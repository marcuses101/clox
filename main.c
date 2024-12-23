#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(int argc, const char *argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN, 1414);
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 1414);
  writeChunk(&chunk, constant, 1414);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);

  return 0;
}

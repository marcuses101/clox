#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  // setup
  initVM();
  Chunk chunk;
  initChunk(&chunk);

  // load instructions

  // 4 - 3 * -2

  // -2
  writeConstant(&chunk, 2, 1);
  writeChunk(&chunk, OP_NEGATE, 2);

  writeConstant(&chunk, 3, 1);
  writeChunk(&chunk, OP_MULTIPLY, 2);
  writeChunk(&chunk, OP_NEGATE, 2);

  writeConstant(&chunk, 4, 1);
  writeChunk(&chunk, OP_ADD, 2);

  writeChunk(&chunk, OP_RETURN, 2);

  // run code
  disassembleChunk(&chunk, "test chunk");
  interpret(&chunk);

  // cleanup
  freeVM();
  freeChunk(&chunk);

  return 0;
}

#include "vm.h"
#include "chunk.h"
#include "compiler.h"
#include "debug.h"
#include "stack.h"
#include "value.h"
#include <stdint.h>
#include <stdlib.h>

VM vm;
Stack stack;

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double a = pop();                                                          \
    double b = pop();                                                          \
    push(a op b);                                                              \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value *slot = vm.stack->array; slot < vm.stack->stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_CONSTANT_LONG: {
      int constantIndex = ((READ_BYTE() << 16) & 0xFF) |
                          ((READ_BYTE() << 8) & 0xFF) | (READ_BYTE() & 0xFF);
      Value constant = vm.chunk->constants.values[constantIndex];
      push(constant);
      break;
    }
    case OP_NEGATE: {
      /* *(vm.stackTop - 1) *= -1; */
      push(-pop());
      break;
    }
    case OP_ADD: {
      BINARY_OP(+);
      break;
    }
    case OP_SUBTRACT: {
      BINARY_OP(-);
      break;
    }
    case OP_MULTIPLY: {
      BINARY_OP(*);
      break;
    }
    case OP_DIVIDE: {
      BINARY_OP(/);
      break;
    }
    case OP_RETURN: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

static void resetStack() { vm.stack->stackTop = vm.stack->array; }

void initVM() {
  vm.stack = &stack;
  initStack(vm.stack);
}
void freeVM() { freeStack(vm.stack); }

InterpretResult interpret(const char *source) {
  compile(source);
  return INTERPRET_OK;
}

void push(Value value) { stackPush(vm.stack, value); }

Value pop() { return stackPop(vm.stack); }

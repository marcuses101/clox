#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "stack.h"
#include "value.h"
#include "object.h"


typedef struct {
  Chunk *chunk;
  uint8_t* ip;
  Stack *stack;
  Object* objects;
} VM;


typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
void push(Value value);
Value pop();
InterpretResult interpret(const char* source);

extern VM vm;

#endif

#include <assert.h>

#include "memory.h"
#include "stack.h"

void initStack(Stack *stack) {
  stack->capacity = 0;
  stack->array = NULL;
  stack->stackTop = NULL;
};

void freeStack(Stack *stack) {
  FREE_ARRAY(Value, stack->array, stack->capacity);
  initStack(stack);
};

int stackSize(Stack *stack) { return stack->stackTop - stack->array; }

void printStack(Stack *stack, const char *tag) {
  printf("\n== %s ==\n", tag);
  printf("capacity: %i\narray: %p\nstackTop: %p\nsize: %i\n", stack->capacity,
         stack->array, stack->stackTop, stackSize(stack));
  printf("!= %s =!\n\n", tag);
}

void stackPush(Stack *stack, Value value) {
  int stackSize = stack->stackTop - stack->array;
  if (stackSize >= stack->capacity) {
    int oldCapacity = stack->capacity;
    stack->capacity = GROW_CAPACITY(oldCapacity);
    stack->array =
        GROW_ARRAY(Value, stack->array, oldCapacity, stack->capacity);
    if (stack->stackTop == NULL) {
      stack->stackTop = stack->array;
    } else {
      stack->stackTop = stack->array + stackSize;
    }
  }
  *stack->stackTop = value;
  stack->stackTop++;
}

Value stackPop(Stack *stack) {
  stack->stackTop--;
  return *stack->stackTop;
}

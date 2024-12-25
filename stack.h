#ifndef clox_stack_h
#define clox_stack_h

#include "common.h"
#include "value.h"

typedef struct {
    int capacity;
    Value* array;
    Value* stackTop;
} Stack;

void stackPush(Stack *stack, Value value);
Value stackPop(Stack *stack);
void printStack(Stack *stack, const char* tag);
void initStack(Stack* stack);
void freeStack(Stack* stack);


#endif

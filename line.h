#ifndef clox_line_h
#define clox_line_h

#include "common.h"

typedef struct {
  int lineNumber;
  int count;
} Line;

typedef struct {
  int capacity;
  int count;
  Line *lineNumbers;
  int lastLineNumber;
} Lines;

void initLines(Lines *lines);
void addLineNumberOccurence(Lines *lines, int lineNumber);
void freeLines(Lines *lines);
int getLine(Lines *lines, int instructionIndex);

#endif

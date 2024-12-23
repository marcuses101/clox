#include <assert.h>

#include "line.h"
#include "memory.h"

void initLines(Lines *lines) {
  lines->count = 0;
  lines->capacity = 0;
  lines->lineNumbers = NULL;
  lines->lastLineNumber = 0;
};

void addLineNumberOccurence(Lines *lines, int lineNumber) {
  if (lines->capacity < lines->count + 1) {
    int oldCapacity = lines->capacity;
    lines->capacity = GROW_CAPACITY(oldCapacity);
    lines->lineNumbers =
        GROW_ARRAY(Line, lines->lineNumbers, oldCapacity, lines->capacity);
  }
  if (lineNumber == 0 || lineNumber != lines->lastLineNumber) {
    lines->lineNumbers[lines->count] =
        (Line){.lineNumber = lineNumber, .count = 0};
    lines->lastLineNumber = lineNumber;
    lines->count++;
  }
  lines->lineNumbers[lines->count - 1].count++;
};

void freeLines(Lines *lines) {
  FREE_ARRAY(Line, lines->lineNumbers, lines->capacity);
  initLines(lines);
};

int getLine(Lines *lines, int instructionIndex) {
  int remaining = instructionIndex;
  int lineIndex = 0;
  Line currentLine = lines->lineNumbers[lineIndex];
  while (currentLine.count <= remaining) {
    assert(lines->count > lineIndex);
    remaining -= lines->lineNumbers[lineIndex].count;
    lineIndex++;
    if (lines->count <= lineIndex) {
      break;
    }
    currentLine = lines->lineNumbers[lineIndex];
  }
  return lines->lineNumbers[lineIndex].lineNumber;
}

void printLines(Lines *lines) {
  for (int i = 0; i < lines->count; i++) {
    printf("%4i,%04i\n", lines->lineNumbers[i].lineNumber,
           lines->lineNumbers[i].count);
  }
}

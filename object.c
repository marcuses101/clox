#include "object.h"
#include "memory.h"
#include "table.h"
#include "value.h"
#include "vm.h"
#include <stdint.h>
#include <string.h>

static Object *allocateObject(size_t size, ObjectType type) {
  Object *object = (Object *)reallocate(NULL, 0, size);
  object->type = type;
  object->next = vm.objects;
  vm.objects = object;
  return object;
}

#define ALLOCATE_OBJECT(type, objectType)                                      \
  (type *)allocateObject(sizeof(type), objectType)

ObjectString *allocateString(char *chars, int length, uint32_t hash) {
  ObjectString *string = ALLOCATE_OBJECT(ObjectString, OBJECT_STRING);
  string->length = length;
  string->chars = chars;
  string->hash = hash;
  tableSet(&vm.strings, string, NIL_VAL);
  return string;
}

uint32_t hashString(const char *key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 1677619;
  }
  return hash;
}

ObjectString *copyString(const char *chars, int length) {
  uint32_t hash = hashString(chars, length);
  ObjectString *interned = tableFindString(&vm.strings, chars, length, hash);
  if (interned != NULL) {
    return interned;
  }
  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length, hash);
}

void printObject(Value value) {
  switch (OBJECT_TYPE(value)) {
  case OBJECT_STRING: {
    printf("%s", AS_C_STRING(value));
  }
  }
}

ObjectString *takeString(char *chars, int length) {
  uint32_t hash = hashString(chars, length);
  ObjectString *interned = tableFindString(&vm.strings, chars, length, hash);
  if (interned != NULL) {
    FREE_ARRAY(char, chars, length + 1);
    return interned;
  }

  return allocateString(chars, length, hash);
}

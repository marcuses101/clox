#ifndef clox_object_h
#define clox_object_h

#include "chunk.h"
#include "common.h"
#include "memory.h"
#include "value.h"

typedef enum { OBJECT_STRING, OBJECT_FUNCTION } ObjectType;

struct Object {
  ObjectType type;
  struct Object *next;
};

typedef struct {
  Object obj;
  int arity;
  Chunk chunk;
  ObjectString *name;
} ObjectFunction;

struct ObjectString {
  Object object;
  int length;
  char *chars;
  uint32_t hash;
};

ObjectFunction *newFunction();

ObjectString *copyString(const char *chars, int length);
ObjectString *takeString(char *chars, int length);

void printObject(Value value);

#define OBJECT_TYPE(value) (AS_OBJECT(value)->type)
#define IS_STRING(value) isObjectType(value, OBJECT_STRING)
#define IS_FUNCTION(value) isObjectType(value, OBJECT_FUNCTION)

#define AS_STRING(value) ((ObjectString *)AS_OBJECT(value))
#define AS_C_STRING(value) (((ObjectString *)AS_OBJECT(value))->chars)

#define AS_FUNCTION(value) ((ObjectFunction *)AS_OBJECT(value))

#define ALLOCATE(type, count)                                                  \
  (type *)reallocate(NULL, 0, sizeof(type) * (count))

static inline bool isObjectType(Value value, ObjectType type) {
  return IS_OBJECT(value) && AS_OBJECT(value)->type == type;
}

#endif

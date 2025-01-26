#ifndef clox_table_h
#define clox_table_h

#include "common.h"
#include "value.h"

typedef struct {
    ObjectString* key;
    Value value;
} Entry;


typedef struct {
    int count;
    int capacity;
    Entry* entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableSet(Table* table, ObjectString* key, Value value);
void tableAddAll(Table* from, Table* to);
ObjectString* tableFindString(Table* table, const char* chars, int length, uint32_t hash);
bool tableGet(Table* table, ObjectString* key, Value* value);
bool tableDelete(Table* table, ObjectString* key);

#endif

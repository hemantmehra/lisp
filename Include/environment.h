#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stddef.h>
#include "object.h"
#include "symbolobject.h"

#define MIN_TABLE_SIZE 8

typedef struct{
	SymbolObject* key;
	Object* val;
}Entry;

typedef struct{
	size_t size;
	size_t used;
	Entry* table;
}Env;

Env* new_env();
void store(SymbolObject*, Object*);
Object* lookup(SymbolObject*);
#define ENTRY_EMPTY(e) ((e.key == NULL && e.val == NULL)? 1 : 0)

int hash(SymbolObject*);

#endif
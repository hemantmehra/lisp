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
void store(Env*, SymbolObject*, Object*);
#define Store(e, sym, o) (store(e, sym, OBJECT_CAST(o)))
Object* Lookup(Env*, SymbolObject*);

#define ENTRY_EMPTY(e) (e.key == NULL && e.val == NULL)

int hash(SymbolObject*);

#endif
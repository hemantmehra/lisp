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

struct _env{
	size_t size;
	size_t used;
	Entry* table;
	struct _env* next_env;
};

typedef struct _env Env;

Env* new_env();
void store(Env*, SymbolObject*, Object*);
#define Store(e, sym, o) (store(e, sym, OBJECT_CAST(o)))
Object* Lookup(Env*, SymbolObject*);

void resize(Env*);

#define ENTRY_EMPTY(e) (e.key == NULL && e.val == NULL)

int hash(SymbolObject*);

#endif
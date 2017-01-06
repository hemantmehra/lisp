#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "object.h"
#include "symbolobject.h"
#include "environment.h"

int hash(SymbolObject* s){
	return SYMBOL_NAME(s)[0];
}

Env* new_env(){
	Env* e;
	e = (Env *) malloc(sizeof(Env));
	e->size = MIN_TABLE_SIZE;
	e->used = 0;
	e->table = (Entry *) malloc(sizeof(Entry) * MIN_TABLE_SIZE);
	memset(e->table, 0, sizeof(Entry) * MIN_TABLE_SIZE);
	return e;
}
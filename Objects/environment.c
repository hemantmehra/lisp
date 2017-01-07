#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

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

void store(Env* e, SymbolObject* key, Object* val){
	int index, j;

	index = hash(key) % e->size;

	j = index;
	do{
		if(ENTRY_EMPTY(e->table[j])){
			e->table[j].key = key; 
			e->table[j].val = val;
		}
		else{ 
			j = ((5 * j) + 1) % (e->size);
		}
	}while(j != index);

	e->used++;
}

Object* Lookup(Env* e, SymbolObject* key){
	int index, j;

	index = hash(key) % e->size;
	j = index;
	do{
		if(ENTRY_EMPTY(e->table[j])) 
			break;	
		if(SYMBOL_EQ(e->table[j].key, key))
			return e->table[j].val;
		else 
			j = ((5 * j) + 1) % (e->size);

	}while(j != index);

	return NULL;
}
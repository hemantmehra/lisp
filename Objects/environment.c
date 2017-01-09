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
	int index, j,a;

	index = hash(key) % e->size;

	j = index;
	do{
		if(ENTRY_EMPTY(e->table[j])){
			e->table[j].key = key; 
			e->table[j].val = val;
			break;
		}
		else{ 
			j = ((5 * j) + 1) % (e->size);
		}
	}while(j != index);

	e->used++;
	a=((2*e->size)/3);
	if(e->used=a)
		{resize(e);
		}
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
void resize(Env* e);
{
	int n;
	n=e->size;
	Entry *prev_table;
prev_table=e->table;
e->size=2*e->size;
e->table = (Entry *) malloc(sizeof(Entry) *e->size);
	memset(e->table, 0, sizeof(Entry) *e->size);
for(i=0;i<n;i++)
	store(Env* e,SymbolObject* prev_table[i].key,Object* prev_table[i].val);

}
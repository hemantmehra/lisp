#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "symbolobject.h"

SymbolObject* new_symbol_object(){
	SymbolObject* sym_obj;
	sym_obj = (SymbolObject *) malloc(sizeof(SymbolObject));
	sym_obj->type = SYMBOL;
	return sym_obj;
}

SymbolObject* Symbol(char* name){
	SymbolObject* sym_obj;
	int len;
	sym_obj = new_symbol_object();
	len = strlen(name);
	sym_obj->name = (char *) calloc(sizeof(char), len + 1);
	strcpy(sym_obj->name, name);
	return sym_obj;
}
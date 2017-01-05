#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "symbolobject.h"

SymbolObject* Symbol(char* name){
	SymbolObject* sym_obj;
	int len;
	len = strlen(name);
	sym_obj = (SymbolObject *) malloc(sizeof(SymbolObject) + len);
	sym_obj->type = SYMBOL;
	strcpy(sym_obj->name, name);
	return sym_obj;
}
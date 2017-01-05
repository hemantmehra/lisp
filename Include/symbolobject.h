#ifndef SYMBOL_OBJECT_H
#define SYMBOL_OBJECT_H

#include "object.h"

struct _symbol_object{
	OBJECT_HEAD;
	char name[1];
};

typedef struct _symbol_object SymbolObject;

#define SYMBOL_OBJECT_CAST(obj) ((SymbolObject *) obj)
#define SYMBOL_NAME(obj) (SYMBOL_OBJECT_CAST(obj)->name)

SymbolObject* Symbol(char*);

#endif
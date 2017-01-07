#ifndef SYMBOL_OBJECT_H
#define SYMBOL_OBJECT_H

#include <string.h>
#include "object.h"

struct _symbol_object{
	OBJECT_HEAD;
	char name[1];
};

typedef struct _symbol_object SymbolObject;

#define SYMBOL_OBJECT_CAST(obj) ((SymbolObject *) obj)
#define SYMBOL_NAME(obj) (SYMBOL_OBJECT_CAST(obj)->name)
#define SYMBOL_EQ(s1, s2) (strcmp(SYMBOL_NAME(s1), SYMBOL_NAME(s2)) == 0)

SymbolObject* Symbol(char*);

#endif
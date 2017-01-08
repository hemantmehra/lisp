#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "stringobject.h"

StringObject* String(char* str){
	StringObject* sym_obj;
	int len;
	len = strlen(str);
	sym_obj = (StringObject *) malloc(sizeof(StringObject) + len);
	sym_obj->type = STRING;
	strcpy(sym_obj->str, str);
	return sym_obj;
}
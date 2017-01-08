#ifndef STRING_OBJECT_H
#define STRING_OBJECT_H

#include <string.h>
#include "object.h"

typedef struct{
	OBJECT_HEAD;
	char str[1];
}StringObject;


#define STRING_OBJECT_CAST(obj) ((StringObject *) obj)
#define STRING(obj) (STRING_OBJECT_CAST(obj)->str)
#define STRING_EQ(s1, s2) (strcmp(STRING(s1), STRING(s2)) == 0)

StringObject* String(char*);

#endif
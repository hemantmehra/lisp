#ifndef INT_OBJECT_H
#define INT_OBJECT_H

#include "object.h"

struct _int_object{
	OBJECT_HEAD;
	int val;
};

typedef struct _int_object IntObject;

#define INT_OBJECT_CAST(obj) ((IntObject *) obj)
#define INT_VAL(obj) (INT_OBJECT_CAST(obj)->val)
#define INT_EQ(i1, i2) (INT_VAL(i1) == INT_VAL(i2))

IntObject* new_int_object();
IntObject* Int(int);

#endif
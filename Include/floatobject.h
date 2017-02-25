#ifndef FLOAT_OBJECT_H
#define FLOAT_OBJECT_H

#include <stdlib.h>
#include "object.h"

struct _float_object{
	OBJECT_HEAD;
	float val;
};

typedef struct _float_object FloatObject;

#define FLOAT_OBJECT_CAST(obj) ((FloatObject *) obj)
#define FLOAT_VAL(obj) (FLOAT_OBJECT_CAST(obj)->val)
#define FLOAT_EQ(obj1, obj2) (FLOAT_VAL(obj1) == FLOAT_VAL(obj2))

FloatObject* new_float_object();
FloatObject* Float(float);
#define FLoatFromString(f) (Float(atof(f)));

#endif                        
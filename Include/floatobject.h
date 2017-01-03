#ifndef FLOAT_OBJECT_H
#define FLOAT_OBJECT_H

#include "object.h"

struct _float_object{
	OBJECT_HEAD;
	float val;
};

typedef struct _float_object FloatObject;

#define FLOAT_OBJECT_CAST(obj) ((FloatObject *) obj)
#define FLOAT_VAL(obj) (FLOAT_OBJECT_CAST(obj)->val)

FloatObject* new_float_object();
FloatObject* Float(float);

#endif                        
#ifndef BOOL_OBJECT_H
#define BOOL_OBJECT_H

#include "object.h"

enum _bool_type{
	FALSE,
	TRUE
};

typedef enum _bool_type BoolType;

struct _boolean_object{
	OBJECT_HEAD;
	BoolType val;
};

typedef  struct _boolean_object BoolObject;

#define BOOL_OBJECT_CAST(obj) ((BoolObject *) obj)
#define BOOL_VAL(obj) (BOOL_OBJECT_CAST(obj)->val)
#define BOOL_EQ(b1, b2) (BOOL_VAL(b1) == BOOL_VAL(b2))
#define OBJECT_BOOL_VAL(obj) (ObjectBoolVal(OBJECT_CAST(obj)))

BoolObject* new_bool_object();
BoolObject* Bool(int);
BoolType ObjectBoolVal(Object*);

#endif
#ifndef NIL_OBJECT_H
#define NIL_OBJECT_H

#include "object.h"

struct _nil_object{
	OBJECT_HEAD;
};

typedef  struct _nil_object NilObject;

#define NIL_OBJECT_CAST(obj) ((NilObject *) obj)

NilObject* new_nil_object();
NilObject* Nil();

#endif
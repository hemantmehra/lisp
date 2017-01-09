#ifndef CLOSURE_OBJECT_H
#define CLOSURE_OBJECT_H

#include "object.h"
#include "environment.h"

typedef struct{
	OBJECT_HEAD;
	Object *bound_vars;
	Object *body;
	Env* env;
}ClosureObject;


#define CLOSURE_OBJECT_CAST(obj) ((ClosureObject *) obj)
#define CLOSURE_BOUND_VARS(obj) (CLOSURE_OBJECT_CAST(obj)->bound_vars)
#define CLOSURE_BODY(obj) (CLOSURE_OBJECT_CAST(obj)->body)
#define CLOSURE_ENV(obj) (CLOSURE_OBJECT_CAST(obj)->env)

ClosureObject* new_closure_object();
ClosureObject* Closure(Object*, Object*, Env*);
#endif
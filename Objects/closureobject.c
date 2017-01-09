#include <stdlib.h>

#include "object.h"
#include "closureobject.h"

ClosureObject* new_closure_object(){
	ClosureObject* c;
	c = (ClosureObject *) malloc(sizeof(ClosureObject));
	c->type = CLOSURE;
	return c;
}

ClosureObject* Closure(Object* bound_vars, Object* body, Env* env){
	ClosureObject* c;
	c = new_closure_object();
	c->bound_vars = bound_vars;
	c->body = body;
	c->env = env;
	return c;
}
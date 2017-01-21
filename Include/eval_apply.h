#ifndef EVAL_APPLY_H
#define EVAL_APPLY_H

#include "object.h"
#include "environment.h"

#define Eval(obj, env) eval(OBJECT_CAST(obj), env)
Object* eval(Object*, Env*);
Object* eval_cond(Object*, Env*);
Object* eval_clause(Object*, Env*);
Object* ev_list(Object*, Env*);

#define Apply(obj1, obj2) apply(OBJECT_CAST(obj1), OBJECT_CAST(obj2))
Object* apply(Object*, Object*);
Object* apply_prim(Object*, Object*);
Object* add(Object*);
Object* sub(Object*);
Object* mul(Object*);
Object* div(Object*);
Object* mod(Object*);
Object* bin_add(Object*, Object*);
Object* bin_sub(Object*, Object*);
Object* bin_mul(Object*, Object*);
Object* bin_div(Object*, Object*);
Object* bin_mod(Object*, Object*);
Object* cons(Object*);
Object* car(Object*);
Object* cdr(Object*);
Object* list(Object*);

Env* extend_env(Env*, Object*, Object*);



#endif
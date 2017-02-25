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
Object* op_add(Object*);
Object* op_sub(Object*);
Object* op_mul(Object*);
Object* op_div(Object*);  
Object* op_mod(Object*);
Object* bin_add(Object*, Object*);
Object* bin_sub(Object*, Object*);
Object* bin_mul(Object*, Object*);
Object* bin_div(Object*, Object*);
Object* bin_mod(Object*, Object*);
Object* op_cons(Object*);
Object* op_car(Object*);
Object* op_cdr(Object*);
Object* op_list(Object*);
Object* op_eq(Object*);
Object* op_gt(Object*);
Object* op_lt(Object*);

Env* extend_env(Env*, Object*, Object*);



#endif
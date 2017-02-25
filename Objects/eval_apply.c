#include "eval_apply.h"
#include "consobject.h"
#include "boolobject.h"
#include "nilobject.h"
#include "list.h"
#include "types.h"
#include "symbolobject.h"
#include "primprocobject.h"
#include "closureobject.h"
#include "environment.h"

Object* eval(Object* exp, Env* env){
	if(IS_SELF_EVAL(exp)) {
		return exp;
	}
	else if(IS_VAR(exp)){
		return Lookup(env, SYMBOL_OBJECT_CAST(exp));
	}
	else if(IS_QUOTE_EXP(exp)){
		return CAR(CDR(exp));
	}
	else if(IS_DEF_EXP(exp)){
		Store(env, SYMBOL_OBJECT_CAST(DEF_VAR(exp)), eval(DEF_VAL(exp), env));
		return DEF_VAR(exp);
	}
	else if(IS_IF_EXP(exp)){
		if(OBJECT_BOOL_VAL(eval(IF_PRED(exp), env)) == TRUE){
			return Eval(IF_CONSQ(exp), env);
		}
		else{
			return Eval(IF_ALTER(exp), env);
		}
	}
	else if(IS_COND_EXP(exp)){
		return eval_cond(exp, env);
	}
	else if(IS_LAMBDA_EXP(exp)){
		return OBJECT_CAST(Closure(LAMBDA_BOUND_VARS(exp), LAMBDA_BODY(exp), env));
	}
	else{
		return apply(Eval(CAR(exp), env), ev_list(CDR(exp), env));
	}
}

Object* apply(Object* proc, Object* args){
	if(IS_PRIM_PROC(proc)){
		return apply_prim(proc, args);
	}
	else if(IS_CLOSURE(proc)){
		return Eval(CLOSURE_BODY(proc), extend_env(CLOSURE_ENV(proc), CLOSURE_BOUND_VARS(proc), args));
	}
}


Object* eval_cond(Object* cond_exp, Env* env){
	Object *p, *result;
	p = CDR(cond_exp);

	while(!IS_NIL(p)){
		result = eval_clause(CAR(p), env);
		if(IS_NIL(result)){
			p = CDR(p);
		}
		else{
			return result;
		}
	}
}

Object* eval_clause(Object* clause, Env* env){
	Object* result;
	if(IS_ELSE_CLAUSE(clause)){
		return eval(CLAUSE_EXP(clause), env);
	}
	else{
		result = eval(CLAUSE_TEST(clause), env);
		if(BOOL_VAL(result) == TRUE){
			return eval(CLAUSE_EXP(clause), env);
		}
		else{
			return OBJECT_CAST(Nil());
		}
	}
}

Object* ev_list(Object* l, Env* env){
	Object *p, *n, *new_l;
	ConsObject* node;

	if(IS_NIL(l)){
		return l;
	}
	else{
		p = l;
		node = Node(eval(CAR(p), env));
		p = CDR(p);
		new_l = OBJECT_CAST(node);
		n = new_l;
		while(!IS_NIL(p)){
			node = Node(eval(CAR(p), env));
			CDR(n) = OBJECT_CAST(node);
			p = CDR(p);
			n = CDR(n);
		}
		CDR(n) = OBJECT_CAST(Nil());
		return new_l;
	}
}

Env* extend_env(Env* env, Object* bound_vars, Object* args){
	Env* ne;
	Object *v, *a;
	ne = new_env();
	v = bound_vars;
	a = args;
	while(!IS_NIL(v) && !IS_NIL(a)){
		Store(ne, SYMBOL_OBJECT_CAST(CAR(v)), CAR(a));
		v = CDR(v);
		a = CDR(a);
	}
	ne->next_env = env;
	return ne;
}

Object* apply_prim(Object* proc, Object* args){
	switch(PRIM_PROC_OP(proc)){
		case ADD_OP: return op_add(args);
		case SUB_OP: return op_sub(args);
		case MUL_OP: return op_mul(args);
		case DIV_OP: return op_div(args);
		case MOD_OP: return op_mod(args);
		case CONS_OP: return op_cons(args);
		case CAR_OP: return op_car(args);
		case CDR_OP: return op_cdr(args);
		case LIST_OP: return op_list(args);
		case EQ_OP: return op_eq(args);
		case GT_OP: return op_gt(args);
		case LT_OP: return op_lt(args);
	}
}

Object* op_add(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_add(OBJECT_CAST(CAR(args)), op_add(OBJECT_CAST(CDR(args))));
	}
}

Object* bin_add(Object* obj1, Object* obj2){
	FloatObject* fs;
	IntObject* is;
	if(IS_FLOAT(obj1) && IS_FLOAT(obj2)){
		fs = Float(0);
		FLOAT_VAL(fs) = FLOAT_VAL(obj1) + FLOAT_VAL(obj2);
		return OBJECT_CAST(fs);
	}
	else if(IS_FLOAT(obj1) || IS_FLOAT(obj2)){
		fs = Float(0);
		if(IS_INT(obj1)){
			FLOAT_VAL(fs) = INT_VAL(obj1) + FLOAT_VAL(obj2);
		}
		else{
			FLOAT_VAL(fs) = FLOAT_VAL(obj1) + INT_VAL(obj2);
		}
		return OBJECT_CAST(fs);
	}
	else{
		is = Int(0);
		INT_VAL(is) = INT_VAL(obj1) + INT_VAL(obj2);
		return OBJECT_CAST(is);
	}
}

Object* op_sub(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_sub(OBJECT_CAST(CAR(args)), op_sub(OBJECT_CAST(CDR(args))));
	}
}

Object* bin_sub(Object* obj1, Object* obj2){
	FloatObject* fs;
	IntObject* is;
	if(IS_FLOAT(obj1) && IS_FLOAT(obj2)){
		fs = Float(0);
		FLOAT_VAL(fs) = FLOAT_VAL(obj1) - FLOAT_VAL(obj2);
		return OBJECT_CAST(fs);
	}
	else if(IS_FLOAT(obj1) || IS_FLOAT(obj2)){
		fs = Float(0);
		if(IS_INT(obj1)){
			FLOAT_VAL(fs) = INT_VAL(obj1) - FLOAT_VAL(obj2);
		}
		else{
			FLOAT_VAL(fs) = FLOAT_VAL(obj1) - INT_VAL(obj2);
		}
		return OBJECT_CAST(fs);
	}
	else{
		is = Int(0);
		INT_VAL(is) = INT_VAL(obj1) - INT_VAL(obj2);
		return OBJECT_CAST(is);
	}
}

Object* op_mul(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_mul(OBJECT_CAST(CAR(args)), op_mul(OBJECT_CAST(CDR(args))));
	}
}

Object* bin_mul(Object* obj1, Object* obj2){
	FloatObject* fs;
	IntObject* is;
	if(IS_FLOAT(obj1) && IS_FLOAT(obj2)){
		fs = Float(0);
		FLOAT_VAL(fs) = FLOAT_VAL(obj1) * FLOAT_VAL(obj2);
		return OBJECT_CAST(fs);
	}
	else if(IS_FLOAT(obj1) || IS_FLOAT(obj2)){
		fs = Float(0);
		if(IS_INT(obj1)){
			FLOAT_VAL(fs) = INT_VAL(obj1) * FLOAT_VAL(obj2);
		}
		else{
			FLOAT_VAL(fs) = FLOAT_VAL(obj1) * INT_VAL(obj2);
		}
		return OBJECT_CAST(fs);
	}
	else{
		is = Int(0);
		INT_VAL(is) = INT_VAL(obj1) * INT_VAL(obj2);
		return OBJECT_CAST(is);
	}
}

Object* op_div(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_div(OBJECT_CAST(CAR(args)), op_div(OBJECT_CAST(CDR(args))));
	}
}

Object* bin_div(Object* obj1, Object* obj2){
	FloatObject* fs;
	IntObject* is;
	if(IS_FLOAT(obj1) && IS_FLOAT(obj2)){
		fs = Float(0);
		FLOAT_VAL(fs) = FLOAT_VAL(obj1) / FLOAT_VAL(obj2);
		return OBJECT_CAST(fs);
	}
	else if(IS_FLOAT(obj1) || IS_FLOAT(obj2)){
		fs = Float(0);
		if(IS_INT(obj1)){
			FLOAT_VAL(fs) = INT_VAL(obj1) / FLOAT_VAL(obj2);
		}
		else{
			FLOAT_VAL(fs) = FLOAT_VAL(obj1) / INT_VAL(obj2);
		}
		return OBJECT_CAST(fs);
	}
	else{
		is = Int(0);
		INT_VAL(is) = INT_VAL(obj1) / INT_VAL(obj2);
		return OBJECT_CAST(is);
	}
}

Object* op_mod(Object* args){
	return bin_mod(OBJECT_CAST(CAR(args)), OBJECT_CAST(CAR(CDR(args))));
}

Object* bin_mod(Object* obj1, Object* obj2){
	return OBJECT_CAST(Int(INT_VAL(obj1) % INT_VAL(obj2)));
}

Object* op_cons(Object* args){
	ConsObject* c;
	c = Cons(CAR(args), CAR(CDR(args)));
	return OBJECT_CAST(c);
}

Object* op_car(Object* args){
	return OBJECT_CAST(CAR(CAR(args)));
}

Object* op_cdr(Object* args){
	return OBJECT_CAST(CDR(CAR(args)));
}

Object* op_list(Object* args){
	return args;
}

Object* op_eq(Object* args){
	Object *o1, *o2;
	BoolObject* b;
	o1 = CAR(args);
	o2 = CAR(CDR(args));
	b = OBJECT_EQ(o1, o2) ? Bool(TRUE) : Bool(FALSE);
	return OBJECT_CAST(b);
}

Object* op_gt(Object* args){
	Object *o1, *o2;
	BoolObject* b;
	float f1, f2;
	o1 = CAR(args);
	o2 = CAR(CDR(args));
	if(IS_INT(o1)) f1 = (float) INT_VAL(o1);
	if(IS_INT(o2)) f2 = (float) INT_VAL(o2);
	if(IS_FLOAT(o1)) f1 = FLOAT_VAL(o1);
	if(IS_FLOAT(o2)) f2 = FLOAT_VAL(o2);
	b = f1 > f2 ? Bool(TRUE) : Bool(FALSE);
	return OBJECT_CAST(b);
}

Object* op_lt(Object* args){
	Object *o1, *o2;
	BoolObject* b;
	float f1, f2;
	o1 = CAR(args);
	o2 = CAR(CDR(args));
	if(IS_INT(o1)) f1 = (float) INT_VAL(o1);
	if(IS_INT(o2)) f2 = (float) INT_VAL(o2);
	if(IS_FLOAT(o1)) f1 = FLOAT_VAL(o1);
	if(IS_FLOAT(o2)) f2 = FLOAT_VAL(o2);
	b = f1 < f2 ? Bool(TRUE) : Bool(FALSE);
	return OBJECT_CAST(b);
}

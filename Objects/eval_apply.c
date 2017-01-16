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
		if(OBJECT_EQ(eval(IF_PRED(exp), env), Bool(TRUE))){
			return eval(IF_CONSQ(exp), env);
		}
		else{
			return eval(IF_ALTER(exp), env);
		}
	}
	else if(IS_COND_EXP(exp)){
		return eval_cond(CDR(exp), env);
	}
	else if(IS_LAMBDA_EXP(exp)){
		return OBJECT_CAST(Closure(LAMBDA_BOUND_VARS(exp), LAMBDA_BODY(exp), env));
	}
	else{
		return apply(CAR(exp), ev_list(CDR(exp), env));
	}
}

Object* apply(Object* proc, Object* args){
	if(IS_PRIM_PROC(proc)){
		return apply_prim(proc, args);
	}
	else if(IS_CLOSURE(proc)){
		return eval(CLOSURE_BODY(proc), extend_env(CLOSURE_ENV(proc), CLOSURE_BOUND_VARS(proc), args));
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
		case ADD: return add(args);
		case SUB: return sub(args);
		case MUL: return mul(args);
		case DIV: return div(args);
		case MOD: return mod(args);
	}
}

Object* add(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_add(OBJECT_CAST(CAR(args)), add(OBJECT_CAST(CDR(args))));
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

Object* sub(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_sub(OBJECT_CAST(CAR(args)), sub(OBJECT_CAST(CDR(args))));
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

Object* mul(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_mul(OBJECT_CAST(CAR(args)), mul(OBJECT_CAST(CDR(args))));
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

Object* div(Object* args){
	if(IS_NIL(CDR(args))){
		return OBJECT_CAST(CAR(args));
	}
	else{
		return bin_div(OBJECT_CAST(CAR(args)), div(OBJECT_CAST(CDR(args))));
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

Object* mod(Object* args){
	return bin_mod(OBJECT_CAST(CAR(args)), OBJECT_CAST(CDR(args)));
}

Object* bin_mod(Object* obj1, Object* obj2){
	return OBJECT_CAST(Int(INT_VAL(obj1) % INT_VAL(obj2)));
}


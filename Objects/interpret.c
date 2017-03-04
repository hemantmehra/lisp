#include "interpret.h"

void init_env(){
	g_env = new_env();

	Store(g_env, Symbol("+"), PrimProc(ADD_OP));
	Store(g_env, Symbol("-"), PrimProc(SUB_OP));
	Store(g_env, Symbol("*"), PrimProc(MUL_OP));
	Store(g_env, Symbol("/"), PrimProc(DIV_OP));
	Store(g_env, Symbol("rem"), PrimProc(MOD_OP));
	Store(g_env, Symbol("cons"), PrimProc(CONS_OP));
	Store(g_env, Symbol("car"), PrimProc(CAR_OP));
	Store(g_env, Symbol("cdr"), PrimProc(CDR_OP));
	Store(g_env, Symbol("list"), PrimProc(LIST_OP));
	Store(g_env, Symbol("="), PrimProc(EQ_OP));
	Store(g_env, Symbol(">"), PrimProc(GT_OP));
	Store(g_env, Symbol("<"), PrimProc(LT_OP));
}

Object* interpret(char *str){
	Token *t;
	Object *l;
	t = tokenizer(str);
	l = tree(t);
	return Eval(l, GLOBAL_ENV);
}
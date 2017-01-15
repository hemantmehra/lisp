#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "object.h"
#include "intobject.h"
#include "consobject.h"
#include "boolobject.h"
#include "nilobject.h"
#include "floatobject.h"
#include "symbolobject.h"
#include "list.h"
#include "environment.h"
#include "stringobject.h"
#include "types.h"
#include "primprocobject.h"
#include "closureobject.h"
#include "eval_apply.h"

void intobject_test(){
	IntObject *i1;
	i1 = Int(45);
	assert(TYPE(i1) == INTEGER);
	assert(INT_VAL(i1) == 45);
}


void consobject_test(){
	IntObject *i1, *i2;
	ConsObject* cobj;

	i1 = Int(45);
	i2 = Int(35);

	cobj = Cons(i1, i2);
	assert(TYPE(cobj) == CONS);
	assert(INT_VAL(CAR(cobj)) == 45);
	assert(INT_VAL(CDR(cobj)) == 35);
}

void boolobject_test(){
	BoolObject *b1, *b2;
	b1 = Bool(TRUE);
	b2 = Bool(FALSE);

	assert(TYPE(b1) == BOOLEAN && TYPE(b2) == BOOLEAN);
	assert(BOOL_VAL(b1) == TRUE);
	assert(BOOL_VAL(b2) == FALSE);
}

void nilobject_test(){
	NilObject *nil;
	nil = Nil();
	assert(TYPE(nil) == NIL);
}

void floatobject_test(){
	FloatObject *f;
	f = Float(20.5);
	assert(FLOAT_VAL(f) == 20.5);
	assert(TYPE(f) == FLOAT);
}

void symbolobject_test(){
	SymbolObject* s;
	s = Symbol("variable1");
	assert(TYPE(s) == SYMBOL);
	assert(strcmp(SYMBOL_NAME(s), "variable1") == 0);
}

void list_test(){
	Object* l;
	l = List(4, Int(10), Float(2.125), Bool(FALSE), Symbol("var1"));

	assert(INT_VAL(CAR(l)) == 10);
	assert(FLOAT_VAL(CAR(CDR(l))) == 2.125);
	assert(BOOL_VAL(CAR(CDR(CDR(l)))) == FALSE);
	assert(strcmp(SYMBOL_NAME(CAR(CDR(CDR(CDR(l))))), "var1") == 0);
	assert(TYPE(CDR(CDR(CDR(CDR(l))))) == NIL);
}

void env_test(){
	Env* e;
	int i;
	e = new_env();
	assert(e->size == MIN_TABLE_SIZE);
	assert(e->used == 0);
	for(i = 0; i < MIN_TABLE_SIZE; i++){
		assert(ENTRY_EMPTY(e->table[i]));
	}

	Store(e, Symbol("a"), Int(1));
	Store(e, Symbol("ab"), Int(2));
	Store(e, Symbol("aab"), Int(3));
	Store(e, Symbol("aaab"), Int(4));
	Store(e, Symbol("aaaab"), Int(5));

	assert(e->used == 5);

	assert(INT_EQ(Lookup(e, Symbol("a")), Int(1)));
	assert(INT_EQ(Lookup(e, Symbol("ab")), Int(2)));
	assert(INT_EQ(Lookup(e, Symbol("aab")), Int(3)));
	assert(INT_EQ(Lookup(e, Symbol("aaab")), Int(4)));
	assert(INT_EQ(Lookup(e, Symbol("aaaab")), Int(5)));

	assert(e->size == MIN_TABLE_SIZE * 2);

}

void stringobject_test(){
	StringObject* s;
	s = String("variable1");
	assert(TYPE(s) == STRING);
	assert(strcmp(STRING(s), "variable1") == 0);
}

void object_eq_test(){
	Object *l1, *l2;
	
	assert(OBJECT_EQ(Int(1), Int(1)));
	assert(OBJECT_EQ(Float(2.125), Float(2.125)));
	assert(OBJECT_EQ(Bool(FALSE), Bool(FALSE)));
	assert(OBJECT_EQ(Symbol("sym"), Symbol("sym")));
	assert(OBJECT_EQ(String("str"), String("str")));
	assert(OBJECT_EQ(Nil(), Nil()));
	assert(OBJECT_EQ(Cons(Int(4), Bool(TRUE)), Cons(Int(4), Bool(TRUE))));

	l1 = List(4, Int(34), Bool(TRUE), Symbol("a"), String("s1"));
	l2 = List(4, Int(34), Bool(TRUE), Symbol("a"), String("s2"));

	assert(OBJECT_EQ(l1, l2));


}
void types_macro_test(){
	Object *l3,*l4,*l5,*l6, *l7, *l8;

	assert(IS_INT(Int(12)));
	assert(IS_FLOAT(Float(12.125)));
	assert(IS_CONS(Cons(Int(12), Float(12.34))));
	assert(IS_SYMBOL(Symbol("var")));
	assert(IS_STRING(String("str1")));
	assert(IS_NIL(Nil()));
	assert(IS_BOOL(Bool(TRUE)));
	assert(IS_PRIM_PROC(PrimProc(SUB)));
	assert(IS_CLOSURE(Closure(List(2, Symbol("x"), Symbol("y")),
		List(3, Symbol("+"), Symbol("x"), Symbol("y")),
		new_env())));

	assert (IS_SELF_EVAL(Int(4))==1);
	assert(IS_VAR(Symbol("a")));
	l3=List(3, DEFINE, Symbol("x"), Int(10));
	assert(IS_DEF_EXP(l3)==1);
	assert(OBJECT_EQ(DEF_VAR(l3), Symbol("x")));
	assert(OBJECT_EQ(DEF_VAL(l3), Int(10)));

	l4=List(4, IF, Symbol("predicate"), Symbol("consq"), Symbol("alternate"));
	l5=List(2, COND,Int(2));
	l6=List(2, QUOTE,Int(3));

	assert(IS_QUOTE_EXP(l6));

	assert(IS_IF_EXP(l4));
	assert(OBJECT_EQ(IF_PRED(l4), Symbol("predicate")));
	assert(OBJECT_EQ(IF_CONSQ(l4), Symbol("consq")));
	assert(OBJECT_EQ(IF_ALTER(l4), Symbol("alternate")));

	assert(IS_COND_EXP(l5));
	assert(IS_ELSE_CLAUSE(List(2, ELSE, Int(1))));
	l7 = List(2, Symbol("test"), Symbol("exp"));
	assert(OBJECT_EQ(CLAUSE_TEST(l7), Symbol("test")));
	assert(OBJECT_EQ(CLAUSE_EXP(l7), Symbol("exp")));

	l8 = List(3, LAMBDA, Symbol("vars"), Symbol("body"));
	assert(IS_LAMBDA_EXP(l8));
	assert(OBJECT_EQ(LAMBDA_BOUND_VARS(l8), Symbol("vars")));
	assert(OBJECT_EQ(LAMBDA_BODY(l8), Symbol("body")));
}

void primprocobject_test(){
	PrimProcObject* p;
	p = PrimProc(ADD);
	assert(TYPE(p) == PRIM_PROC);
	assert(PRIM_PROC_OP(p) == ADD);
}

void closureobject_test(){
	ClosureObject* c;
	Object *vars, *body;
	Env* env;
	vars = List(2, Symbol("x"), Symbol("y"));
	body = List(3, Symbol("+"), Symbol("x"), Symbol("y"));
	env = new_env();

	c = Closure(vars, body, env);
	assert(TYPE(c) == CLOSURE);
	assert(OBJECT_EQ(CLOSURE_BOUND_VARS(c), vars));
	assert(OBJECT_EQ(CLOSURE_BODY(c), body));
}

void eval_test(){
	assert(OBJECT_EQ(Eval(Int(12), new_env()), Int(12)));
}

int main(){
	intobject_test();
	consobject_test();
	boolobject_test();
	nilobject_test();
	floatobject_test();
	symbolobject_test();
	list_test();
	env_test();
	stringobject_test();
	object_eq_test();
	primprocobject_test();
	closureobject_test();
	types_macro_test();
	eval_test();
	printf("Test Successful!!!\n");
	return 0;
}
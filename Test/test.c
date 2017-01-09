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
void eval_test(){
	Object *l3,*l4,*l5,*l6;
	assert (IS_SELF_EVAL(Int(4))==1);
	assert(IS_VAR(Symbol("a")));
	l3=List(3, Symbol("define"), Symbol("x"), Int(10));
	assert(IS_DEF(l3)==1);
	l4=List(4, Symbol("if"), Symbol("predicate"), Symbol("consq"), Symbol("alternate"));
	l5=List(2,Symbol("cond"),Int(2));
	l6=List(2,Symbol("quote"),Int(3));
	assert(IS_QUOTE(l6));
	assert(IS_IF(l4));
	assert(IS_COND(l5));
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
	eval_test();
	printf("Test Successful!!!\n");
	return 0;
}
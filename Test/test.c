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
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "interpret.h"

void intobject_test(){
	printf("IntObject test...");
	IntObject *i1;
	i1 = Int(45);
	assert(TYPE(i1) == INTEGER);
	assert(INT_VAL(i1) == 45);

	printf("Done\n");
}


void consobject_test(){
	printf("ConsObject test...");
	IntObject *i1, *i2;
	ConsObject* cobj;

	i1 = Int(45);
	i2 = Int(35);

	cobj = Cons(i1, i2);
	assert(TYPE(cobj) == CONS);
	assert(INT_VAL(CAR(cobj)) == 45);
	assert(INT_VAL(CDR(cobj)) == 35);

	printf("Done\n");
}

void boolobject_test(){
	printf("BoolObject test...");
	BoolObject *b1, *b2;
	b1 = Bool(TRUE);
	b2 = Bool(FALSE);

	assert(TYPE(b1) == BOOLEAN && TYPE(b2) == BOOLEAN);
	assert(BOOL_VAL(b1) == TRUE);
	assert(BOOL_VAL(b2) == FALSE);
	assert(OBJECT_BOOL_VAL(Int(0)) == FALSE);
	assert(OBJECT_BOOL_VAL(Int(1)) == TRUE);
	assert(OBJECT_BOOL_VAL(Bool(FALSE)) == FALSE);

	printf("Done\n");
}

void nilobject_test(){
	printf("NilObject test...");
	NilObject *nil;
	nil = Nil();
	assert(TYPE(nil) == NIL);

	printf("Done\n");
}

void floatobject_test(){
	printf("FloatObject test...");
	FloatObject *f;
	f = Float(20.5);
	assert(FLOAT_VAL(f) == 20.5);
	assert(TYPE(f) == FLOAT);

	printf("Done\n");
}

void symbolobject_test(){
	printf("SymbolObject test...");
	SymbolObject* s;
	s = Symbol("variable1");
	assert(TYPE(s) == SYMBOL);
	assert(strcmp(SYMBOL_NAME(s), "variable1") == 0);

	printf("Done\n");
}

void list_test(){
	printf("List test...");
	Object* l;
	l = List(4, Int(10), Float(2.125), Bool(FALSE), Symbol("var1"));

	assert(INT_VAL(CAR(l)) == 10);
	assert(FLOAT_VAL(CAR(CDR(l))) == 2.125);
	assert(BOOL_VAL(CAR(CDR(CDR(l)))) == FALSE);
	assert(strcmp(SYMBOL_NAME(CAR(CDR(CDR(CDR(l))))), "var1") == 0);
	assert(TYPE(CDR(CDR(CDR(CDR(l))))) == NIL);

	printf("Done\n");
}

void env_test(){
	printf("Environment test...");
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

	printf("Done\n");

}

void stringobject_test(){
	printf("StringObject test...");
	StringObject* s;
	s = String("variable1");
	assert(TYPE(s) == STRING);
	assert(strcmp(STRING(s), "variable1") == 0);

	printf("Done\n");
}

void object_eq_test(){
	printf("OBJECT_EQ test...");
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

	printf("Done\n");
}
void types_macro_test(){
	printf("types macro test...");
	Object *l3,*l4,*l5,*l6, *l7, *l8;

	assert(IS_INT(Int(12)));
	assert(IS_FLOAT(Float(12.125)));
	assert(IS_CONS(Cons(Int(12), Float(12.34))));
	assert(IS_SYMBOL(Symbol("var")));
	assert(IS_STRING(String("str1")));
	assert(IS_NIL(Nil()));
	assert(IS_BOOL(Bool(TRUE)));
	assert(IS_PRIM_PROC(PrimProc(SUB_OP)));
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

	printf("Done\n");
}

void primprocobject_test(){
	printf("PrimProcObject test...");
	PrimProcObject* p;
	p = PrimProc(ADD_OP);
	assert(TYPE(p) == PRIM_PROC);
	assert(PRIM_PROC_OP(p) == ADD_OP);

	printf("Done\n");
}

void closureobject_test(){
	printf("ClosureObject test...");
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

	printf("Done\n");
}

void ev_list_test(){
	printf("ev_list() test...");
	Object *l1, *l2;
	Env* env;
	l1 = List(3, Float(12.125), Int(10), Bool(TRUE));
	l2 = ev_list(l1, env);
	assert(OBJECT_EQ(l1, l2));

	printf("Done\n");
}

void prim_op_test(){
	printf("Primitive op test...");
	Object *l1,*l2,*l3,*l4,*l5,*l6,*l7,*l8,*l9, *l10, *l11, *l12, *l13;
	l1 = List(3, Int(1), Int(2), Int(3));
	l2 = op_add(l1);
	assert(OBJECT_EQ(l2, Int(6)));
	l3=List(2,Int(20),Int(10));
	l4=op_sub(l3);
	assert(OBJECT_EQ(l4, Int(10)));
	l5=op_mul(l1);
	assert(OBJECT_EQ(l5,Int(6)));
	l6=List(2,Int(20),Int(10));

	l7=op_div(l6);
	assert(OBJECT_EQ(l7,Int(2)));
	
	l8=List(2,Int(13),Int(4));
    l9=op_mod(l8);
	assert(OBJECT_EQ(l9,Int(1)));

	l10 = List(2, Int(10), Int(12));
	l11 = op_cons(l10);
	assert(OBJECT_EQ(op_car(List(1, l11)), Int(10)) && OBJECT_EQ(op_cdr(List(1, l11)), Int(12)));

	l12 = op_list(l1);
	assert(OBJECT_EQ(l12, l1));

	l13 = List(2, Int(10), Int(10));
	
	assert(OBJECT_EQ(op_eq(l6), Bool(FALSE)));
	assert(OBJECT_EQ(op_gt(l6), Bool(TRUE)));
	assert(OBJECT_EQ(op_lt(l6), Bool(FALSE)));
	assert(OBJECT_EQ(op_gt(l10), Bool(FALSE)));	
	assert(OBJECT_EQ(op_lt(l10), Bool(TRUE)));
	assert(OBJECT_EQ(op_eq(l13), Bool(TRUE)));

	printf("Done\n");
}
void extend_env_test(){
	printf("extend_env() test...");
	Object *l1,*l2;
	Env *ne,*e;
	e=new_env();
	l1=List(2,Symbol("x"),Symbol("y"));
	l2=List(2,Int(3),Int(4));
	ne=extend_env(e,l1,l2);
	assert(INT_EQ(Eval(Symbol("x"),ne), Int(3)));
	assert(INT_EQ(Eval(Symbol("y"),ne), Int(4)));

	printf("Done\n");
}

void eval_clause_test(){
	printf("eval_clause() test...");
	Object *c;
	Env*  env;
	env = new_env();
	c = List(2, ELSE, Int(1));
	assert(OBJECT_EQ(eval_clause(c, env), Int(1)));

	c = List(2, Bool(FALSE), Int(1));
	assert(OBJECT_EQ(eval_clause(c, env), Nil()));

	c = List(2, Bool(TRUE), Int(1));
	assert(OBJECT_EQ(eval_clause(c, env), Int(1)));

	printf("Done\n");	
}

void eval_cond_test(){
	printf("eval_cond() test...");
	Object *l1,*C1,*C2,*C3;
	Env*  env;
	env=new_env();
	Store(env, Symbol("="), PrimProc(EQ_OP));
	Store(env, Symbol(">"), PrimProc(GT_OP));
	Store(env, Symbol("<"), PrimProc(LT_OP));

	C1=List(2, Bool(FALSE),Int(0));
	C2=List(2,Bool(TRUE),Int(1));
	C3=List(2, Bool(TRUE),Int(2));
	l1=List(4, COND,C1,C2,C3);
	assert(OBJECT_EQ(eval_cond(l1,env),Int(1)));

	Store(env, Symbol("n"), Int(0));

	C1 = List(2, List(3, Symbol("="), Symbol("n"), Int(0)), Int(0));
	C2 = List(2, List(3, Symbol(">"), Symbol("n"), Int(0)), Int(1));
	C3 = List(2, List(3, Symbol("<"), Symbol("n"), Int(0)), Int(-1));
	l1 = List(4, COND, C1, C2, C3);
	assert(IS_COND_EXP(l1));
	assert(OBJECT_EQ(eval_cond(l1, env), Int(0)));

	printf("Done\n");
}


void eval_test(){
	printf("eval_test() test...");
	Object *l1, *l2, *l3, *l4, *l5, *l6,*l7,*l8,*l9;
	Env* env;
	env = new_env();
	assert(OBJECT_EQ(Eval(Int(12), env), Int(12)));

	l1 = List(3, DEFINE, Symbol("x"), Int(10));
	assert(OBJECT_EQ(Eval(l1, env), Symbol("x")));
	assert(OBJECT_EQ(Eval(Symbol("x"), env), Int(10)));

	l2 = List(2, QUOTE, Symbol("x"));
	assert(OBJECT_EQ(Eval(l2, env), Symbol("x")));

	Store(env, Symbol("+"), PrimProc(ADD_OP));
	
	l4 = List(3, Symbol("+"), Int(10), Int(12));
	assert(OBJECT_EQ(Eval(l4, env), Int(22)));

	l5 = List(4, IF, Bool(FALSE), String("T"), String("F"));
	assert(OBJECT_EQ(Eval(l5, env), String("F")));

	l6 = List(4, LAMBDA, List(1, Symbol("x")), List(3, Symbol("+"), Symbol("x"), Int(1)));
	Object* c = Eval(l6, env);
	assert(OBJECT_EQ(CLOSURE_BOUND_VARS(c), List(1, Symbol("x"))));
	assert(OBJECT_EQ(CLOSURE_BODY(c), List(3, Symbol("+"), Symbol("x"), Int(1))));

	l7=List(3,Symbol("+"),Symbol("x"),Int(3));
	l8=List(3,LAMBDA,List(1,Symbol("x")),l7);
	l9=List(2,l8,Int(4));
	assert(INT_EQ(Eval(l9,env),Int(7)));

	printf("Done\n");
}

void basic_prog_test(){
	printf("Basic program test...");
	Object *func, *func_body, *bound_vars, *lambda,*clause1,*clause2, *clause3,*else_clause, 
		*appl1, *appl2, *if_exp, *pred_exp, *consq_exp, *alter_exp,*l2;
	Env* env;
	env = new_env();

	Store(env, Symbol("+"), PrimProc(ADD_OP));
	Store(env, Symbol("-"), PrimProc(SUB_OP));
	Store(env, Symbol("*"), PrimProc(MUL_OP));
	Store(env, Symbol("/"), PrimProc(DIV_OP));
	Store(env, Symbol("rem"), PrimProc(MOD_OP));
	Store(env, Symbol("cons"), PrimProc(CONS_OP));
	Store(env, Symbol("car"), PrimProc(CAR_OP));
	Store(env, Symbol("cdr"), PrimProc(CDR_OP));
	Store(env, Symbol("list"), PrimProc(LIST_OP));
	Store(env, Symbol("="), PrimProc(EQ_OP));
	Store(env, Symbol(">"), PrimProc(GT_OP));
	Store(env, Symbol("<"), PrimProc(LT_OP));

	/*	Sqaure Function test
	 	(define sqr 
			(lambda (x)
					(* x x)))
		(sqr 9) should eval to 81
		(sqr 21) should eval to 441
	*/
	func_body = List(3, Symbol("*"), Symbol("x"), Symbol("x"));
	bound_vars = List(1, Symbol("x"));
	lambda = List(3, LAMBDA, bound_vars, func_body);
	func = List(3, DEFINE, Symbol("sqr"), lambda);
	Eval(func, env);

	appl1 = List(2, Symbol("sqr"), Int(9));
	assert(OBJECT_EQ(Eval(appl1, env), Int(81)));

	appl2 = List(2, Symbol("sqr"), Int(21));
	assert(OBJECT_EQ(Eval(appl2, env), Int(441)));

	/* Fact function
	(define fact
	       (lambda (n) 
	       	   (if (= n 0)
	       	   	   1 
	       	   	   (* n (fact(- n 1)))))

	      (fact 0) should eval to 1
	       (fact 5) should eval to 120
	  */
	bound_vars = List(1, Symbol("n"));
	pred_exp = List(3, Symbol("="), Symbol("n"), Int(0));
	consq_exp = OBJECT_CAST(Int(1));
	alter_exp = List(3,Symbol("*"),Symbol("n"),List(2, Symbol("fact"), List(3, Symbol("-"), Symbol("n"), Int(1))));

	if_exp=List(4,Symbol("if"), pred_exp, consq_exp, alter_exp);
	lambda = List(3, LAMBDA, bound_vars,if_exp);
	func=List(3,DEFINE,Symbol("fact"),lambda);
	Eval(func, env);

	appl1=List(2, Symbol("fact"), Int(0));
	assert(OBJECT_EQ(Eval(appl1, env), Int(1)));

	appl2=List(2, Symbol("fact"), Int(5));
	assert(OBJECT_EQ(Eval(appl2, env), Int(120)));

	/* sum of sqr
	(define sos
       (lambda (x y)
             (+ (sqr x) 
             	(sqr y))))
     */
    bound_vars=List(2,Symbol("x"),Symbol("y"));
    func_body=List(3,Symbol("+"),List(2,Symbol("sqr"),Symbol("x")),List(2,Symbol("sqr"),Symbol("y")));
    lambda=List(3,LAMBDA,bound_vars,func_body);
    func=List(3,DEFINE,Symbol("sos"),lambda);
	Eval(func, env);

	appl1=List(3, Symbol("sos"), Int(2),Int(3));
	assert(OBJECT_EQ(Eval(appl1, env), Int(13)));

	appl2=List(3, Symbol("sos"), Int(3),Int(4));
	assert(OBJECT_EQ(Eval(appl2, env), Int(25)));


	/* cond test
		(define func
			(lambda (n)
				(cond ((= n 0) 0)
					  ((> n 0) 1)
					  ((< n 0) -1))))
	*/

	bound_vars = List(1, Symbol("n"));
	clause1 = List(2, List(3, Symbol("="), Symbol("n"), Int(0)), Symbol("n"));
	clause2 = List(2, List(3, Symbol(">"), Symbol("n"), Int(0)), Int(1));
	clause3 = List(2, List(3, Symbol("<"), Symbol("n"), Int(0)), Int(-1));

	func_body = List(4, COND, clause1, clause2, clause3);
	lambda = List(3, LAMBDA, bound_vars, func_body);
	func = List(3, DEFINE, Symbol("func"), lambda);
	Eval(func, env);
	appl1 = List(2, Symbol("func"), Int(0));
	assert(OBJECT_EQ(Eval(appl1, env), Int(0)));

	/* fibo test
	(define fibo 
		(lambda (n) 
			(cond ((= n 0) 0) 
				  ((= n 1) 1) 
				  (else (+  (fibo(- n 1))
				  			(fibo(- n 2)))))))
	*/

	
	bound_vars=List(1,Symbol("n"));
	clause1=List(2,List(3,Symbol("="),Symbol("n"),Int(0)),Int(0));
	clause2=List(2,List(3,Symbol("="),Symbol("n"),Int(1)),Int(1));
	else_clause=List(2, ELSE,List(3,Symbol("+"),List(2,Symbol("fibo"),List(3,Symbol("-"),Symbol("n"),Int(1))),List(2,Symbol("fibo"),List(3,Symbol("-"),Symbol("n"),Int(2)))));
	func_body=List(4,Symbol("cond"),clause1,clause2,else_clause);
	lambda=List(3,LAMBDA,bound_vars,func_body);
	func=List(3,DEFINE,Symbol("fibo"),lambda);
	Eval(func,env);
	appl1=List(2,Symbol("fibo"),Int(5));
	assert(OBJECT_EQ(Eval(appl1,env),Int(5)));
        
	
	/* fibo test
	(define fibo1 
	      (lambda (n) 
	         (if (< n 2) 
	         	 n 
	         	 (+ (fibo(- n 1)) 
	         	 	(fibo(- n 2))))))
    */
	
	bound_vars=List(1,Symbol("n"));
	pred_exp = List(3, Symbol("<"), Symbol("n"), Int(2));
	consq_exp = OBJECT_CAST(Symbol("n"));
	alter_exp = List(3,Symbol("+"),List(2,Symbol("fibo1"),List(3,Symbol("-"),Symbol("n"),Int(1))),List(2,Symbol("fibo"),List(3,Symbol("-"),Symbol("n"),Int(2))));
	func_body=List(4,Symbol("if"), pred_exp, consq_exp,alter_exp);
	lambda=List(3,LAMBDA,bound_vars,func_body);
	func=List(3,DEFINE,Symbol("fibo1"),lambda);
	Eval(func,env);
	appl1=List(2,Symbol("fibo1"),Int(5));
	assert(OBJECT_EQ(Eval(appl1,env),Int(5)));

	/*(define complex
    (lambda (x y)
        (Cons x y)
        ))*/
	bound_vars=List(2,Symbol("x"),Symbol("y"));
	func_body=List(3,Symbol("cons"),Symbol("x"),Symbol("y"));
	lambda=List(3,LAMBDA,bound_vars,func_body);
	func=List(3,DEFINE,Symbol("complex"),lambda);
	Eval(func, env);

	/*(define real
	(lambda (cn)
	   (car cn)
	 ))*/

	bound_vars=List(1,Symbol("cn"));
	func_body=List(2,Symbol("car"),Symbol("cn"));
	lambda=List(3,LAMBDA,bound_vars,func_body);
	func=List(3,DEFINE,Symbol("real"),Symbol("car"));
	Eval(func, env);

	/*(define imag
	(lambda (cn)
	(cdr cn)
	))*/
	bound_vars=List(1,Symbol("cn"));
	func_body=List(2,Symbol("cdr"),Symbol("cn"));
	lambda=List(3,LAMBDA,bound_vars,func_body);
	func=List(3,DEFINE,Symbol("imag"),Symbol("cdr"));
	Eval(func, env);

	/* (define add-complex
	(lambda (c1 c2)
	(complex (+ (real c1) (real c2)) (+ (imag c1) (imag c2)))

	))*/
	bound_vars=List(2,Symbol("c1"),Symbol("c2"));
	func_body=List(3,Symbol("complex"),List(3,Symbol("+"),List(2,Symbol("real"),Symbol("c1")),List(2,Symbol("real"),Symbol("c2"))),List(3,Symbol("+"),List(2,Symbol("imag"),Symbol("c1")),List(2,Symbol("imag"),Symbol("c2"))));
	lambda=List(3,LAMBDA,bound_vars,func_body);
	func=List(3,DEFINE,Symbol("add-complex"),lambda);
	Eval(func, env);


	/*2 complex numbers:
	(define a (complex 1 2))
	(define b (complex 3 4))*/

	appl1=List(3,DEFINE,Symbol("a"),List(3,Symbol("complex"),Int(1),Int(2)));
	appl2=List(3,DEFINE,Symbol("b"),List(3,Symbol("complex"),Int(3),Int(4)));
	Object* re=Eval(appl1,env);
	assert(OBJECT_EQ(CAR(Eval(Symbol("a"),env)),Int(1)));                        
	assert(OBJECT_EQ(CDR(Eval(Symbol("a"),env)),Int(2)));
	Object* re1=Eval(appl2,env);
	assert(OBJECT_EQ(CAR(Eval(Symbol("b"),env)),Int(3)));                        
	assert(OBJECT_EQ(CDR(Eval(Symbol("b"),env)),Int(4)));
	appl1=List(2, Symbol("real"), Symbol("a"));
	appl2=List(2, Symbol("imag"), Symbol("a"));

	assert(OBJECT_EQ(Eval(appl1, env), Int(1)));
	assert(OBJECT_EQ(Eval(appl2, env), Int(2)));

	appl1=List(3,DEFINE,Symbol("c"),List(3,Symbol("add-complex"),Symbol("a"),Symbol("b")));

	Eval(appl1,env);
	assert(IS_CONS(Eval(Symbol("c"),env)));
	assert(OBJECT_EQ(CAR(Eval(Symbol("c"),env)),Int(4)));                        
	assert(OBJECT_EQ(CDR(Eval(Symbol("c"),env)),Int(6)));

	printf("Done\n");

}

void lexer_test(){
	printf("Lexer test...");

	m_init();
	m_reset();
	m_putchar('t');
	m_putchar('o');
	m_putchar('k');
	m_putchar('e');
	m_putchar('n');
	assert(strcmp(m_getstring(), "token") == 0);

	m_reset();
	assert(strcmp(m_getstring(), "") == 0);
	assert(minus_func('-')==1);
	assert(plus_func('+')==1);
	assert(dquote_func('\"')==1);
	assert(digit_func('8')==1);
	assert(sym_char_func('a')==1);
	assert(whitespace_func(' ')==1);
	assert(rp_func(')')==1);
	assert(lp_func('(')==1);

	m_reset();
	assert(m_getcurrlabel() == s_q0);
	m_changestate(s_lp);
	assert(m_getcurrlabel() == s_lp);

	Token *t;
	t = tokenizer("     (        define   x 10.125      )        ");
	assert(TOKEN_TYPE(t) == T_LP);
	t = t->next;
	assert(TOKEN_TYPE(t) == T_SYMBOL && (strcmp(SYMBOL_NAME(t->obj), "define") == 0));
	t = t->next;
	assert(TOKEN_TYPE(t) == T_SYMBOL && (strcmp(SYMBOL_NAME(t->obj), "x") == 0));
	t = t->next;
	assert(TOKEN_TYPE(t) == T_FLOAT && FLOAT_VAL(t->obj) == 10.125);
	t = t->next;
	assert(TOKEN_TYPE(t) == T_RP);
	t = t->next;
	assert(t == NULL);

	t = tokenizer("(1 (2 3) 4)");
	assert(TOKEN_TYPE(t) == T_LP);
	t = t->next;
	assert(TOKEN_TYPE(t) == T_INT && INT_VAL(t->obj) == 1 );
	t = t->next;
	assert(TOKEN_TYPE(t) == T_LP);
	t = t->next;
	assert(TOKEN_TYPE(t) == T_INT && INT_VAL(t->obj) == 2 );
	t = t->next;
	assert(TOKEN_TYPE(t) == T_INT && INT_VAL(t->obj) == 3 );
	t = t->next;
	assert(TOKEN_TYPE(t) == T_RP);
	t = t->next;
	assert(TOKEN_TYPE(t) == T_INT && INT_VAL(t->obj) == 4 );
	t = t->next;
	assert(TOKEN_TYPE(t) == T_RP);
	t = t->next;
	assert(t == NULL);

	printf("Done\n");
}

void token_test(){
	printf("Token test...");

	Token *t;

	t = IntToken("-23");
	assert(TOKEN_TYPE(t) == T_INT);
	assert(INT_VAL(t->obj) == -23);
	printf("Done\n");
}

void parser_test(){
	printf("Parser test...");

	Token *t;
	t = tokenizer("(define \n x \n 10.125)");
	Object *l, *l1;
	l = tree(t);
	l1 = List(3, DEFINE, Symbol("x"), Float(10.125));
	assert(OBJECT_EQ(l, l1));

	t = tokenizer("(1 (2 3) 4)");
	l = tree(t);
	l1 = List(3, Int(1),  List(2, Int(2), Int(3)), Int(4));
	assert(OBJECT_EQ(l, l1));

	t = tokenizer("(1 2 (3 4 (5 6)))");
	l = tree(t);
	l1 = List(3, Int(1), Int(2), List(3, Int(3), Int(4), List(2, Int(5), Int(6))));
	assert(OBJECT_EQ(l, l1));

	printf("Done\n");
}

void interpret_test(){
	printf("Interpret test...");
	Object *obj;
	
	init_env();
	obj = interpret("(+ 3 6)");
	assert(OBJECT_EQ(obj, Int(9)));

	interpret("(define x 10)");
	interpret("(define y 30)");

	obj = interpret("(* x y)");
	assert(OBJECT_EQ(obj, Int(300)));

	char *code = "(define sqr \
					(lambda (x) \
					(* x x)))";
	interpret(code);
	obj = interpret("(sqr 25)");
	assert(OBJECT_EQ(obj, Int(625)));


	char *code1 = "(define isZero (lambda (n) (if (= n 0) 1 0)))";
	interpret(code1);
	obj = interpret("(isZero 0)");
	assert(OBJECT_EQ(obj, Int(1)));


	char *code2 = "(define fact (lambda (n) (if (= n 0) 1 (* n (fact (- n 1))))))";
	interpret(code2);
	obj = interpret("(fact 5)");
	assert(OBJECT_EQ(obj, Int(120)));

	printf("Done\n");
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
	ev_list_test();
	prim_op_test();
	extend_env_test();
	eval_cond_test();
	eval_clause_test();
	eval_test();
	basic_prog_test();
	lexer_test();
	token_test();
	parser_test();
	interpret_test();
	printf("--------------------------------\n");
	printf("Test Successful!!!\n");
	printf("--------------------------------\n");
	return 0;
}
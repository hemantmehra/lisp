#ifndef TYPES_H
#define TYPES_H

#include "object.h"
#include "intobject.h"
#include "consobject.h"
#include "boolobject.h"
#include "nilobject.h"
#include "floatobject.h"
#include "symbolobject.h"
#include "stringobject.h"

#define OBJECT_EQ(obj1, obj2) (object_eq(OBJECT_CAST(obj1), OBJECT_CAST(obj2)))
#define TYPE_EQ(obj1, obj2) (OBJECT_CAST(obj1)->type == OBJECT_CAST(obj2)->type)
int object_eq(Object*, Object*);

#define IS_INT(exp) (TYPE(exp)==INTEGER)
#define IS_FLOAT(exp) (TYPE(exp)==FLOAT)
#define IS_CONS(exp) (TYPE(exp) == CONS)
#define IS_SYMBOL(exp) (TYPE(exp)==SYMBOL)
#define IS_STRING(exp) (TYPE(exp)==STRING)
#define IS_NIL(exp) (TYPE(exp)==NIL)
#define IS_BOOL(exp) (TYPE(exp)==BOOLEAN)
#define IS_PRIM_PROC(proc) (TYPE(proc) == PRIM_PROC)
#define IS_CLOSURE(proc) (TYPE(proc) == CLOSURE)

#define IS_SELF_EVAL(exp) (IS_INT(exp)||IS_FLOAT(exp)||IS_STRING(exp)||IS_NIL(exp)||IS_BOOL(exp))
#define IS_VAR(exp) (IS_SYMBOL(exp))

#define DEFINE Symbol("define")
#define IS_DEF_EXP(exp) (SYMBOL_EQ(CAR(exp), DEFINE))
#define DEF_VAR(exp) (CAR(CDR(exp)))
#define DEF_VAL(exp) (CAR(CDR(CDR(exp))))

#define QUOTE Symbol("quote")
#define IS_QUOTE_EXP(exp) (SYMBOL_EQ(CAR(exp), QUOTE))

#define IF Symbol("if")
#define IS_IF_EXP(exp) (SYMBOL_EQ(CAR(exp), IF))
#define IF_PRED(exp) (CAR(CDR(exp)))
#define IF_CONSQ(exp) (CAR(CDR(CDR(exp))))
#define IF_ALTER(exp) (CAR(CDR(CDR(CDR(exp)))))

#define COND Symbol("cond")
#define IS_COND_EXP(exp) (SYMBOL_EQ(CAR(exp), COND))
#define ELSE Symbol("else")
#define IS_ELSE_CLAUSE(exp) (SYMBOL_EQ(CAR(exp), ELSE))
#define CLAUSE_TEST(clause) (CAR(clause))
#define CLAUSE_EXP(clause) (CAR(CDR(clause)))

#define LAMBDA Symbol("lambda")
#define IS_LAMBDA_EXP(exp) (SYMBOL_EQ(CAR(exp), LAMBDA))
#define LAMBDA_BOUND_VARS(exp) (CAR(CDR(exp)))
#define LAMBDA_BODY(exp) (CAR(CDR(CDR(exp))))


#endif
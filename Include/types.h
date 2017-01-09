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

#define IS_SELF_EVAL(exp) (IS_INT(exp)||IS_FLOAT(exp)||IS_SYMBOL(exp)||IS_NIL(exp)||IS_BOOL(exp))
#define IS_INT(exp) (TYPE(exp)==INTEGER)
#define IS_FLOAT(exp) (TYPE(exp)==FLOAT)
#define IS_SYMBOL(exp) (TYPE(exp)==SYMBOL)
#define IS_NIL(exp) (TYPE(exp)==NIL)
#define IS_BOOL(exp) (TYPE(exp)==BOOLEAN)
#define IS_VAR(exp) (IS_SYMBOL(exp))
#define IS_DEF(exp) (SYMBOL_EQ(CAR(exp),Symbol("define")))
#define IS_QUOTE(exp) (SYMBOL_EQ(CAR(exp),Symbol("quote")))
#define IS_IF(exp) (SYMBOL_EQ(CAR(exp),Symbol("if")))
#define IS_COND(exp) (SYMBOL_EQ(CAR(exp),Symbol("cond")))
#endif
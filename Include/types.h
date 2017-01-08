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

#endif
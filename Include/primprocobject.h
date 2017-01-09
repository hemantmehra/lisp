#ifndef PRIM_PROC_OBJECT_H
#define PRIM_PROC_OBJECT_H

#include "object.h"

typedef enum{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD
} PrimitiveOp;

typedef struct{
	OBJECT_HEAD;
	PrimitiveOp op;
}PrimProcObject;

#define PRIM_PROC_OBJECT_CAST(obj) ((PrimProcObject *) obj)
#define PRIM_PROC_OP(obj) (PRIM_PROC_OBJECT_CAST(obj)->op)

PrimProcObject* new_prim_proc_object();
PrimProcObject* PrimProc(PrimitiveOp);



#endif
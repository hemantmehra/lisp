#ifndef PRIM_PROC_OBJECT_H
#define PRIM_PROC_OBJECT_H

#include "object.h"

typedef enum{
	ADD_OP,
	SUB_OP,
	MUL_OP,
	DIV_OP,
	MOD_OP,
	CONS_OP,
	CAR_OP,
	CDR_OP,
	LIST_OP
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
#include <stdlib.h>

#include "object.h"
#include "primprocobject.h"

PrimProcObject* new_prim_proc_object(){
	PrimProcObject* p;
	p = (PrimProcObject *) malloc(sizeof(PrimProcObject));
	p->type = PRIM_PROC;
	return p;
}

PrimProcObject* PrimProc(PrimitiveOp op){
	PrimProcObject* p;
	p = new_prim_proc_object();
	p->op = op;
	return p;
}
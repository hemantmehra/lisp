#include <stdlib.h>
#include "nilobject.h"

NilObject* new_nil_object(){
	NilObject* nil_obj;
	nil_obj = (NilObject *) malloc(sizeof(NilObject));
	nil_obj->type = NIL;
	return nil_obj;
}

NilObject* Nil(){
	NilObject* nil_obj;
	nil_obj = new_nil_object();
	return nil_obj;
}
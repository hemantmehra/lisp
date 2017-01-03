#include <stdlib.h>
#include "object.h"
#include "intobject.h"
#include "consobject.h"
#include "boolobject.h"
#include "nilobject.h"

void del_object(Object* obj){
	if(TYPE(obj) == INTEGER){
		IntObject* int_obj;
		int_obj = INT_OBJECT_CAST(obj);
		free(int_obj);
	}
	else if(TYPE(obj) == CONS){
		ConsObject* cons_obj;
    	cons_obj = CONS_OBJECT_CAST(obj);
    	free(cons_obj);
	}
	else if(TYPE(obj) == BOOLEAN){
		BoolObject* bool_obj;
		bool_obj = BOOL_OBJECT_CAST(obj);
		free(bool_obj);
	}
	else if(TYPE(obj) == NIL){
		NilObject* nil_obj;
		nil_obj = NIL_OBJECT_CAST(obj);
		free(nil_obj);
	}
}
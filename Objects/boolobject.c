#include <stdlib.h>
#include "object.h"
#include "intobject.h"
#include "boolobject.h"

BoolObject* new_bool_object(){
	BoolObject* bool_obj;
	bool_obj = (BoolObject *) malloc(sizeof(BoolObject));
	bool_obj->type = BOOLEAN;
	return bool_obj;
}

BoolObject* Bool(int val){
	BoolObject* bool_obj;
	bool_obj = new_bool_object();
	if(val) bool_obj->val = TRUE;
	else bool_obj->val = FALSE;
	return bool_obj;
}

BoolType ObjectBoolVal(Object* obj){
	switch(TYPE(obj)){
		case BOOLEAN: return BOOL_VAL(obj);
		case INTEGER: return INT_VAL(obj)? TRUE : FALSE;
		case NIL: return FALSE;
		default: return FALSE; 
	}
}
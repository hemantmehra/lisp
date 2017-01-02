#include <stdlib.h>
#include "object.h"
#include "intobject.h"

IntObject* new_int_object(){
	IntObject* int_obj;
	int_obj = (IntObject *) malloc(sizeof(IntObject));
	int_obj->type = INTEGER;
	return int_obj;
}

IntObject* Int(int i){
	IntObject* int_obj;
	int_obj = new_int_object();
	int_obj->val = i;
	return int_obj;
}
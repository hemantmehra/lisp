#include <stdlib.h>
#include "floatobject.h"

FloatObject* new_float_object(){
	FloatObject* float_obj;
	float_obj = (FloatObject *) malloc(sizeof(FloatObject));
	float_obj->type = FLOAT;
	return float_obj;
}

FloatObject* Float(float i){
	FloatObject* float_obj;
	float_obj = new_float_object();
	float_obj->val = i;
	return float_obj;
}
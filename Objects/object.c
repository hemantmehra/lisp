#include <stdlib.h>
#include "object.h"
#include "intobject.h"
#include "consobject.h"

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
}
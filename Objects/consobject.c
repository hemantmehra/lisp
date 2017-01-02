#include <stdlib.h>
#include "object.h"
#include "consobject.h"

ConsObject* new_cons_object(){
	ConsObject* cons_obj;
	cons_obj = (ConsObject *) malloc(sizeof(ConsObject));
	cons_obj->type = CONS;
	return cons_obj;
}

ConsObject* _Cons(Object* obj1, Object* obj2){
	ConsObject* cons_obj;
	cons_obj = new_cons_object();
	cons_obj->car = obj1;
	cons_obj->cdr = obj2;
	return cons_obj;
}
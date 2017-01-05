#include <stddef.h>
#include <stdarg.h>

#include "object.h"
#include "consobject.h"
#include "nilobject.h"
#include "list.h"

ConsObject* Node(Object* obj){
	ConsObject* node;
	node = new_cons_object();
	node->car = obj;
	return node;
}

Object* List(size_t s, ...){
	va_list ap;
	int i;
	Object *obj;
	ConsObject *list, *p;
	va_start(ap, s);

	if(s == 0)
		return OBJECT_CAST(Nil());

	obj = va_arg(ap, Object*);
	list = p = Node(obj);

	for(i = 1; i < s; i++){
		obj = va_arg(ap, Object*);
		p->cdr = OBJECT_CAST(Node(obj));
		p = CONS_OBJECT_CAST(p->cdr);
	}
	va_end(ap);
	p->cdr = OBJECT_CAST(Nil());
	return OBJECT_CAST(list);
}
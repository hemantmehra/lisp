#ifndef CONS_OBJECT_H
#define CONS_OBJECT_H

struct _cons_object{
	OBJECT_HEAD;
	Object *car;
	Object *cdr;
};

typedef struct _cons_object ConsObject;

#define CONS_OBJECT_CAST(obj) ((ConsObject *) obj)
#define CAR(obj) (CONS_OBJECT_CAST(obj)->car)
#define CDR(obj) (CONS_OBJECT_CAST(obj)->cdr)

#define Cons(x, y) (_Cons(OBJECT_CAST(x), OBJECT_CAST(y)))

ConsObject* new_cons_object();
ConsObject* _Cons(Object*, Object*);


#endif
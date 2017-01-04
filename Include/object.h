#ifndef OBJECT_H
#define OBJECT_H


enum _object_type{
	INTEGER,
	FLOAT,
	CONS,
	SYMBOL,
	BOOLEAN,
	STRING,
	CLOSURE,
	NIL
};

typedef enum _object_type ObjectType;

#define OBJECT_HEAD ObjectType type;


struct _object {
	OBJECT_HEAD;
};

typedef struct _object Object;

#define OBJECT_CAST(obj) ((Object *) obj)
#define TYPE(obj) (OBJECT_CAST(obj)->type)

void del_object(Object*);

#endif
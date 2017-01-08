#include "types.h"

int object_eq(Object *obj1, Object *obj2){
	if(TYPE_EQ(obj1, obj2)){
		switch(TYPE(obj1)){
			case INTEGER: return INT_EQ(obj1, obj2);
			case FLOAT: return FLOAT_EQ(obj1, obj2);
			case BOOLEAN: return BOOL_EQ(obj1, obj2);
			case SYMBOL: return SYMBOL_EQ(obj1, obj2);
			case STRING: return STRING_EQ(obj1, obj2);
			case NIL: return 1;
			case CONS: return OBJECT_EQ(CAR(obj1), CAR(obj1)) && OBJECT_EQ(CDR(obj1), CDR(obj2));
		}
	}
	else{
		return 0;
	}

}
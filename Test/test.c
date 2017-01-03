#include <assert.h>
#include <stdio.h>

#include "object.h"
#include "intobject.h"
#include "consobject.h"
#include "boolobject.h"

void intobject_test(){
	IntObject *i1;
	i1 = Int(45);
	assert(TYPE(i1) == INTEGER);
	assert(INT_VAL(i1) == 45);
}


void consobject_test(){
	IntObject *i1, *i2;
	ConsObject* cobj;

	i1 = Int(45);
	i2 = Int(35);

	cobj = Cons(i1, i2);
	assert(TYPE(cobj) == CONS);
	assert(INT_VAL(CAR(cobj)) == 45);
	assert(INT_VAL(CDR(cobj)) == 35);
}

void boolobject_test(){
	BoolObject *b1, *b2;
	b1 = Bool(TRUE);
	b2 = Bool(FALSE);

	assert(TYPE(b1) == BOOLEAN && TYPE(b2) == BOOLEAN);
	assert(BOOL_VAL(b1) == TRUE);
	assert(BOOL_VAL(b2) == FALSE);
}

int main(){
	intobject_test();
	consobject_test();
	boolobject_test();

	printf("Test Successful!!!\n");
	return 0;
}
#include <assert.h>
#include <stdio.h>

#include "intobject.h"
#include "consobject.h"

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

int main(){
	intobject_test();
	consobject_test();

	printf("Test Successful!!!\n");
	return 0;
}
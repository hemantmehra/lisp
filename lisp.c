#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interpret.h"
#include "object.h"
#include "intobject.h"


int main(){
	printf("------------ Lisp Interpreter -------------\n");
	printf("type quit to exit\n");
	init_env();
	while(1){
		printf("lisp>");
		char str[100];
		Object *obj;
		fgets(str, 100, stdin);

		if(strcmp(str, "quit\n") == 0)
			exit(0);

		obj=interpret(str);

		if(TYPE(obj) == INTEGER)
			printf("%d\n", INT_VAL(obj));
		//print_obj(obj);
	}

	return 0;
}
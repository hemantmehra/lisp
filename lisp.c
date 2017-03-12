#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interpret.h"
#include "object.h"
#include "intobject.h"
#include "floatobject.h"
#include "consobject.h"
#include "symbolobject.h"
#include "boolobject.h"
#include "stringobject.h"
#include "primprocobject.h"
#include "closureobject.h"
#include "nilobject.h"

void print_obj(Object*);

int main(){
	char ch, code[1024], str[200];
	int p, i;
	Object *obj;

	printf("------------ Lisp Interpreter -------------\n");
	printf("type quit to exit\n");
	printf("-------------------------------------------\n");
	init_env();
	while(1){
		printf("lisp> ");
		p = 0;
		code[0] = '\0';
		
		do{
			fgets(str, 200, stdin);
			i = 0;
			while((ch = str[i]) != '\0'){
				if(ch == '(')
					p++;
				if(ch == ')')
					p--;
				i++;
			}
			strcat(code, str);
		}while(p!=0);

		if(strcmp(code, "quit\n") == 0)
			exit(0);
		if(strcmp(code, "\n") == 0)
			continue;

		obj=interpret(code);

		print_obj(obj);
		printf("\n");
	}

	return 0;
}


void print_obj(Object* obj){
	switch(TYPE(obj)){
		case INTEGER: 
			printf("%d ", INT_VAL(obj));
			break;
		case FLOAT:
			printf("%f ", FLOAT_VAL(obj));
			break;
		case CONS:
			print_obj(CAR(obj));
			print_obj(CDR(obj));
			break;
		case SYMBOL:
			printf("%s ", SYMBOL_NAME(obj));
			break;
		case BOOLEAN:
			if(BOOL_VAL(obj) == TRUE)
				printf("TRUE ");
			else
				printf("FALSE ");
			break;
		case STRING:
			printf("\"%s\" ", STRING(obj));
			break;
		case PRIM_PROC:
			printf("<Primitive operation> ");
			break;
		case CLOSURE:
			printf("<Closure> ");
			break;
		case NIL:
			printf("NIL ");
	}
}

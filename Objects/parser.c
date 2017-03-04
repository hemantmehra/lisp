#include <stdio.h>
#include "parser.h"
#include "nilobject.h"

Object* tree(Token* l){
	static Token* t;
	Object *p, *curr;
	curr = NULL;
	t = l->next;
	while(1){
		if(TOKEN_TYPE(t) == T_LP){
			p = curr = tree(t);
		}
		else if(TOKEN_TYPE(t) == T_RP){
			CDR(curr) = OBJECT_CAST(Nil());
			return p;
		}
		else{
			if(curr == NULL){
				p = OBJECT_CAST(Node(t->obj));
				curr = p;
			}
			else{
				CDR(curr) = OBJECT_CAST(Node(t->obj));
				curr = CDR(curr);
			}	
		}
		t = t->next;
	}
}
#include <stdlib.h>
#include "token.h"
#include "object.h"
#include "intobject.h"
#include "floatobject.h"
#include "stringobject.h"
#include "symbolobject.h"

Token* new_token(TokenType t1){
	Token *t;
	t=(Token *) malloc(sizeof(Token));
	t->type = t1;
	return t;	
}

void set_obj(Token* t, Object* obj){
	t->obj=obj;
}

Token* TokenLP(){
	Token *t;
	t=new_token(T_LP);
	set_obj(t,NULL);
	return t;
}   
 
Token* TokenRP(){
	Token *t;
	t=new_token(T_RP);
	set_obj(t,NULL);
	return t;
}

Token* TokenFromInt(int i){
	IntObject* int_obj;
	Token *t;
	int_obj=Int(i);
	t=new_token(T_INT);
	set_obj(t, OBJECT_CAST(int_obj));
	return t;
}

Token* TokenFromFloat(float i){
	FloatObject* float_obj;
	Token *t;
	float_obj=Float(i);
	t=new_token(T_FLOAT);
	set_obj(t, OBJECT_CAST(float_obj));
	return t;
}

Token* TokenFromString(char *i){
	StringObject* string_obj;
	Token *t;
	string_obj=String(i);
	t=new_token(T_STRING);
	set_obj(t, OBJECT_CAST(string_obj));
	return t;
}

Token* TokenFromSymbol(char* i){
	SymbolObject* symbol_obj;
	Token *t;
	symbol_obj=Symbol(i);
	t=new_token(T_SYMBOL);
	set_obj(t, OBJECT_CAST(symbol_obj));
	return t;
}
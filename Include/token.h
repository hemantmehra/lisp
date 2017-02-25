#ifndef TOKEN_H
#define TOKEN_H

#include "object.h"

typedef enum{
	T_LP,
	T_RP,
	T_INT,
	T_FLOAT,
	T_STRING,
	T_SYMBOL
}TokenType;

typedef struct token Token ;
struct token{
	TokenType type;
	Object* obj;
	Token *next;
};

#define TOKEN_TYPE(t) (t->type)

Token* new_token(TokenType);
void set_obj(Token*, Object*);
Token* IntToken(char *);                        
Token* FloatToken(char *);                        
Token* StringToken(char *);                        
Token* SymbolToken(char*);
Token* LPToken();
Token* RPToken();

#endif
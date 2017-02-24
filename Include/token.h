#ifndef TOKEN_H
#define TOKEN_H
typedef enum{
T_LP,
T_RP,
T_INT,
T_FLOAT
T_STRING
T_SYMBOL
}TokenType;
typedef struct token Token ;
struct token{
  TokenType type;
  Object* obj;
	Token *next;
};
Token* new_token(TokenType);
void set_obj(Token*, Object*);
Token* TokenFromInt(int);                        
 Token* TokenFromFloat(float);                        
Token* TokenFromString(char *);                        
Token* TokenFromSymbol(char*);
#endif
#include "lexer.h"

void m_reset(){
	lexer_m.b_counter = 0;
	lexer_m.buffer[lexer_m.b_counter] = '\0';
}

void m_putchar(char c){
	lexer_m.buffer[lexer_m.b_counter] = c;
	lexer_m.b_counter++;
}

char* m_getstring(){
	lexer_m.buffer[lexer_m.b_counter] = '\0';
	return lexer_m.buffer;
}
int lp_func(char c) 
 {if(c== '(') return 1; 
 else return 0;}
 
 int rp_func(char c) 
 {if(c== ')') return 1; 
 else return 0;}
 
 
int dquote_func(char c)
{if(c== '\"') 
return 1; 
 else return 0;}


int digit_func(char c)
{if(c>='0'&&c<='9') return 1; 
 else return 0;}


int plus_func(char c)
{if(c== '+') return 1; 
 else return 0;}

int minus_func(char c)
{if(c== '-') return 1; 
 else return 0;}

 int sym_char_func(char c)
 {
if(digit_func(c)||plus_func(c)||minus_func(c))
return 1;
else if(c>=65&&c<91||c>=97&&c<123)
return 1;
else if(c=='/'||c=='*'||c=='%')
return 1;
else
return 0;
}
int whitespace_func(char c)
{if(c == ' '||c=='\t'||c=='\n') return 1; 
 else return 0;}
 
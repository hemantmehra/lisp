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
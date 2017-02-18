#ifndef LEXER_H
#define LEXER_H

typedef enum{
	s_q0,
	s_lp,
	s_rp,
	s_istr,
	s_str,
	s_sym,
	s_int,
	s_float
}Label;

typedef int (* arc_func) (char);
typedef struct arc Arc;
typedef struct state State;

struct state{
	Label l;
	Arc* arcs;
	int arc_c;	
};

struct arc{
	arc_func f;
	State s;
};

typedef struct machine Machine;

struct machine{
	State *s;
	char buffer[50];
	int b_counter;
};

Machine lexer_m;

// Machine functions
void m_reset();
void m_putchar(char);
char* m_getstring();


// Arc functions
int lp_func(char);
int rp_func(char);
int dquote_func(char);
int digit_func(char);
int plus_func(char);
int minus_func(char);
int sym_char_func(char);
int whitespace_func(char);



#endif
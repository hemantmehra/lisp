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
	s_float,
	s_plus,
	s_minus
}Label;

typedef int (* arc_func) (char);
typedef struct arc Arc;
typedef struct state State;

struct state{
	Label l;
	Arc* arcs;
	int arc_c;	
};

State   S_q0,
		S_lp,
		S_rp,
		S_istr,
		S_str,
		S_sym,
		S_int,
		S_float,
		S_plus,
		S_minus;

struct arc{
	arc_func f;
	State s;
};

Arc arc_q0_lp,
	arc_q0_rp,
	arc_q0_istr,
	arc_q0_int,
	arc_q0_plus,
	arc_q0_minus,
	arc_q0_sym,
	arc_q0_q0,

	arc_istr_istr,
	arc_int_int,
	arc_int_float,
	arc_float_float,
	arc_plus_int,
	arc_plus_sym,
	arc_minus_int,
	arc_minus_sym,
	arc_sym_sym,

	arcs_q0[8],
	arcs_istr[1],
	arcs_int[2],
	arcs_float[1],
	arcs_plus[2],
	arcs_minus[2],
	arcs_sym[1];


typedef struct machine Machine;

struct machine{
	State *s;
	char buffer[50];
	int b_counter;
};

Machine lexer_m;

// Machine functions
void m_init();
void m_reset();
void m_putchar(char);
char* m_getstring();


// Arc functions
int lp_func(char);
int rp_func(char);
int dquote_func(char);
int digit_func(char);
int dot_func(char);
int plus_func(char);
int minus_func(char);
int sym_char_func(char);
int whitespace_func(char);
int allchar_func(char);



#endif
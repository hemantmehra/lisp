#include <stdio.h>
#include "lexer.h"

/*
S_q0 = {s_q0, arcs_q0, 8};
S_lp = {s_lp, NULL, 0};
S_rp = {s_rp, NULL, 0;
S_istr = {s_istr, arcs_istr, 2};
S_str = {s_str, NULL, 0};
S_sym = {s_sym, arcs_sym, 1};
S_int = {s_int, arcs_int, 2};
S_float = {s_float, arcs_float, 1};
S_plus = {s_plus, arcs_plus, 2};
S_minus = {s_minus, arcs_minus, 2};

*/

/*
arc_q0_lp = {lp_func, S_lp};
arc_q0_rp = {rp_func, S_rp};
arc_q0_istr = {dquote_func, S_istr};
arc_q0_int = {digit_func, S_int};
arc_q0_plus = {plus_func, S_plus};
arc_q0_minus = {minus_func, S_minus};
arc_q0_sym = {sym_char_func, S_sym};
arc_q0_q0 = {whitespace_func, S_q0};

arc_istr_istr = {allchar_func, S_istr};
arc_istr_str = {dquote_func, S_str}
arc_int_int = {digit_func, S_int};
arc_int_float = {dot_func, S_float};
arc_float_float = {digit_func, S_float};
arc_plus_int = {digit_func, S_int};
arc_plus_sym = {sym_char_func, S_sym};
arc_minus_int = {digit_func, S_int};
arc_minus_sym = {sym_char_func, S_sym};
arc_sym_sym = {sym_char_func, S_sym};

arcs_q0 = {
	arc_q0_lp,
	arc_q0_rp,
	arc_q0_istr,
	arc_q0_int,
	arc_q0_plus,
	arc_q0_minus,
	arc_q0_sym,
	arc_q0_q0
};

arcs_istr = {arc_istr_istr, arc_istr_str};
arcs_int = {arc_int_int, arc_int_float};
arcs_float = {arc_float_float};
arcs_plus = {arc_plus_int, arc_plus_sym};
arcs_minus = {arc_minus_int, arc_minus_sym};
arcs_sym = {arc_sym_sym};

*/

void m_init(){
	S_q0.l = s_q0;
	S_q0.arcs = arcs_q0;
	S_q0.arc_c = 8;

	S_lp.l = s_lp;
	S_lp.arcs = NULL;
	S_lp.arc_c = 0;
	
	S_rp.l = s_rp;
	S_rp.arcs = NULL;
	S_rp.arc_c = 0;

	S_istr.l = s_istr;
	S_istr.arcs = arcs_istr;
	S_istr.arc_c = 2;

	S_str.l = s_str;
	S_str.arcs = NULL;
	S_str.arc_c = 0;

	S_sym.l = s_sym;
	S_sym.arcs = arcs_sym;
	S_sym.arc_c = 1;
	
	S_int.l = s_int;
	S_int.arcs = arcs_int;
	S_int.arc_c = 2;

	S_float.l = s_float;
	S_float.arcs = arcs_float;
	S_float.arc_c = 1;

	S_plus.l = s_plus;
	S_plus.arcs = arcs_plus;
	S_plus.arc_c = 2;

	S_minus.l = s_minus;
	S_minus.arcs = arcs_minus;
	S_minus.arc_c = 2;




	arc_q0_lp.f = lp_func;
	arc_q0_lp.s = S_lp;
	arc_q0_rp.f = rp_func;
	arc_q0_rp.s = S_rp;
	arc_q0_istr.f = dquote_func;
	arc_q0_istr.s = S_istr;
	arc_q0_int.f = digit_func;
	arc_q0_int.s = S_int;
	arc_q0_plus.f = plus_func;
	arc_q0_plus.s = S_plus;
	arc_q0_minus.f = minus_func;
	arc_q0_minus.s = S_minus;
	arc_q0_sym.f = sym_char_func;
	arc_q0_sym.s = S_sym;
	arc_q0_q0.f = whitespace_func;
	arc_q0_q0.s = S_q0;

	arc_istr_istr.f = allchar_func;
	arc_istr_istr.s =  S_istr;
	arc_istr_str.f = dquote_func;
	arc_istr_str.s = S_str;
	arc_int_int.f = digit_func;
	arc_int_int.s = S_int;
	arc_int_float.f = dot_func;
	arc_int_float.s = S_float;
	arc_float_float.f = digit_func;
	arc_float_float.s = S_float;
	arc_plus_int.f = digit_func;
	arc_plus_int.s = S_int;
	arc_plus_sym.f = sym_char_func;
	arc_plus_sym.s = S_sym;
	arc_minus_int.f = digit_func;
	arc_minus_int.s = S_int;
	arc_minus_sym.f = sym_char_func;
	arc_minus_sym.s = S_sym;
	arc_sym_sym.f = sym_char_func;
	arc_sym_sym.s = S_sym;

	
	arcs_q0[0] = arc_q0_lp;
	arcs_q0[1] = arc_q0_rp;
	arcs_q0[2] = arc_q0_istr;
	arcs_q0[3] = arc_q0_int;
	arcs_q0[4] = arc_q0_plus;
	arcs_q0[5] = arc_q0_minus;
	arcs_q0[6] = arc_q0_sym;
	arcs_q0[7] = arc_q0_q0;

	arcs_istr[0] = arc_istr_istr;
	arcs_istr[1] = arc_istr_str;

	arcs_int[0] = arc_int_int;
	arcs_int[1] = arc_int_float;

	arcs_float[0] = arc_float_float;

	arcs_plus[0] = arc_plus_int;
	arcs_plus[1] = arc_plus_sym;

	arcs_minus[0] = arc_minus_int;
	arcs_minus[1] = arc_minus_sym;

	arcs_sym[0] = arc_sym_sym;

	lexer_m.s = &S_q0;
	lexer_m.b_counter = 0;
	lexer_m.buffer[lexer_m.b_counter] = '\0';
}

void m_reset(){
	lexer_m.s = &S_q0;
	lexer_m.b_counter = 0;
	lexer_m.buffer[lexer_m.b_counter] = '\0';
}

void m_changestate(Label l){
	switch(l){
		case s_q0: 
			lexer_m.s = &S_q0;
			break;
		case s_lp: 
			lexer_m.s = &S_lp;
			break;
		case s_rp: 
			lexer_m.s = &S_rp;
			break;
		case s_istr: 
			lexer_m.s = &S_istr;
			break;
		case s_str: 
			lexer_m.s = &S_str;
			break;
		case s_sym: 
			lexer_m.s = &S_sym;
			break;
		case s_int: 
			lexer_m.s = &S_int;
			break;
		case s_float: 
			lexer_m.s = &S_float;
			break;
		case s_plus: 
			lexer_m.s = &S_plus;
			break;
		case s_minus:
			lexer_m.s = &S_minus;
			break;	
	}
}

Label m_getcurrlabel(){
	return lexer_m.s->l;
}

void m_putchar(char c){
	lexer_m.buffer[lexer_m.b_counter] = c;
	lexer_m.b_counter++;
}

char* m_getstring(){
	lexer_m.buffer[lexer_m.b_counter] = '\0';
	return lexer_m.buffer;
}

void tokenizer(char *str){
	char ch;
	int i, n;
	m_init();
	printf("\nTokens: ");
	while((ch = *str) != '\0'){
		n = lexer_m.s->arc_c;
		for(i=0; i<n; i++){
			if(lexer_m.s->arcs[i].f(ch)){
				if(lexer_m.s->arcs[i].s.l != s_q0)
				m_putchar(ch);
				m_changestate(lexer_m.s->arcs[i].s.l);
				str++;
				break;
			}
		}
		if(i == n){
			printf("%s, ", m_getstring());
			m_reset();
		}
	}
	printf("%s\n", m_getstring());
}

int lp_func(char c){
	if(c== '(') return 1; 
 	else return 0;
}
 
int rp_func(char c){
	if(c== ')') return 1; 
	else return 0;
}

int dquote_func(char c){
	if(c== '\"') return 1; 
	else return 0;
}

int digit_func(char c){
	if(c>='0'&&c<='9') return 1; 
 	else return 0;
}

int dot_func(char c){
	if(c == '.') return 1;
	else return 0;
}

int plus_func(char c){
	if(c== '+') return 1; 
 	else return 0;
}

int minus_func(char c){
	if(c== '-') return 1; 
 	else return 0;
}

int sym_char_func(char c){
	if(digit_func(c)||plus_func(c)||minus_func(c)) return 1;
	else if((c>=65&&c<91) || (c>=97&&c<123)) return 1;
	else if(c=='/'||c=='*'||c=='%') return 1;
	else return 0;
}

int whitespace_func(char c){
	if(c == ' '||c=='\t'||c=='\n') return 1; 
	else return 0;
}

int allchar_func(char c){
	return 1;
}
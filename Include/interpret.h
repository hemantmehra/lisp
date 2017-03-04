#ifndef INTERPRET_H
#define INTERPRET_H

#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "eval_apply.h"
#include "environment.h"
#include "primprocobject.h"

#define GLOBAL_ENV g_env
Env *g_env;

void init_env();
Object* interpret(char*);

#endif
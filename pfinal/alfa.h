#ifndef ALFA_H
#define ALFA_H

#include "tablasimbolos.h" //cambiar a tener informacion en alfa.h o en un comun
#include "generacion.h"

#define ERROR 20
#define MAX_VECTOR 64
#define MAX_IDENTIFIER 100
#define VARIABLE 1
#define PARAMETRO 2
#define FUNCION 3

#define INT 1
#define BOOLEAN 2

#define FALSE 0
#define TRUE 1

#define ESCALAR 1
#define VECTOR 2

typedef enum operaciones{
  SUMA, RESTA, MULTIPLICACION, DIVISION, CAMBIO_SIGNO, AND, OR, NOT,
  IGUAL, DISTINTO, MENORIGUAL, MAYORIGUAL, MENOR, MAYOR
}operaciones;

typedef enum s_error{
    dec_dup, undec_acc, arit_bool, log_int, comp_bool, cond_int,
    bucl_cond_int, inc_num_pam, incomp_assgn, size_v, index_in_nov,
    index_noint, f_noret, ret_nof, callf_param, local_nosc, func_as_var,
    noindex_v, funcInsideFunc, errAmbLoc, param_nosc, return_nosc, ret_wrongtype,
    funcIsNotFunc
}s_error;

extern int yylineno;
extern int column;
extern FILE* yyin;
extern FILE* yyout;
int yyerror(char *s);
int error_sem(s_error error, char *identificador);
int error_unknown();
#endif

#ifndef PRUEBASINTACTICO_H
#define PRUEBASINTACTICO_H

extern int yylineno;
extern int column;
extern FILE* yyin;
extern FILE* yyout;
int yyerror(char *s);

#endif
#ifndef PRUEBASINTACTICO_H
#define PRUEBASINTACTICO_H

#define ERROR 20
extern int yylineno;
extern int column;
extern FILE* yyin;
extern FILE* yyout;
int yyerror(char *s);

#endif
#ifndef COMPILER_H
#define COMPILER_H

extern int yylineno;
extern int column;
extern FILE* yyin;
extern FILE* yyout;
int yyerror(char *s);

#endif
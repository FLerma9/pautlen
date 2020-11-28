#ifndef FLEXBISON_H
#define FLEXBISON_H

extern int yylineno;
extern int column;
extern FILE* yyin;
extern FILE* yyout;
extern int yylineno;
int yyerror(char *s);

#endif
%{
    #include <stdio.h>
    #include "alfa.h"
    #include "tablasimbolos.h"
    #include "y.tab.h"
    int next_column = 1, column = 1;
    void emitir_error(char* cadena_error);
    #define YY_USER_ACTION {\
        if(yy_act < YY_NUM_RULES - 3 && yyleng < 100){\
            column = next_column;\
            next_column += yyleng;\
            if(yy_act < YY_NUM_RULES - 5) fprintf(stdout, ";D:\t%s\n", yytext);\
        }\
    }
%}
%option noyywrap noinput nounput yylineno nodefault
%%
main    {return TOK_MAIN;}
int    {return TOK_INT;}
boolean    {return TOK_BOOLEAN;}
array    {return TOK_ARRAY;}
function    {return TOK_FUNCTION;}
if    {return TOK_IF;}
else    {return TOK_ELSE;}
while    {return TOK_WHILE;}
scanf    {return TOK_SCANF;}
printf    {return TOK_PRINTF;}
return    {return TOK_RETURN;}
";" |
"," |
"(" |
")" |
"[" |
"]" |
"{" |
"}" |
"=" |
"+" |
"-" |
"/" |
"*"    {return yytext[0];}

"=="    {return TOK_IGUAL;}
"<="    {return TOK_MENORIGUAL;}
">="    {return TOK_MAYORIGUAL;}
"!="    {return TOK_DISTINTO;}

"&&"    {return TOK_AND;}
"||"    {return TOK_OR;}
"!"    {return TOK_NOT;}
"<"    {return TOK_MENOR;}
">"    {return TOK_MAYOR;}
true    {yylval.atrib.valor_entero = 1; return TOK_TRUE;}
false   {yylval.atrib.valor_entero = 0; return TOK_FALSE;}
[a-zA-Z][a-zA-Z0-9]*    { if(yyleng>MAX_IDENTIFIER){
                            emitir_error("identificador demasiado largo");
                            return ERROR;
                          }
                           strcpy(yylval.atrib.identificador, yytext);
                           return TOK_IDENTIFICADOR;}
[0-9]+    {yylval.atrib.valor_entero = atoi(yytext);
            return TOK_CONSTANTE_ENTERA;}

" " ;
\t ;
\n { next_column = 1;}
"//".*\n ;
. { emitir_error("simbolo no permitido");
    return ERROR;}
%%
void emitir_error(char* cadena_error){
    fprintf(stderr, "****Error en [lin %d, col %d]: %s (%s)\n", yylineno, column+1, cadena_error, yytext);
}

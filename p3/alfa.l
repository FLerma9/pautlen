%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "flexbison.h"
    int next_column = 1, column = 1;
    void emitir_error(char* cadena_error);
    #define ECHO fprintf(yyout, ";D:\t%s\n", yytext)
    #define HANDLE_COLUMN column = next_column; next_column += yyleng        
%}
%option noyywrap noinput nounput yylineno nodefault
%%
main    { HANDLE_COLUMN; ECHO; return TOK_MAIN;}
int    { HANDLE_COLUMN; ECHO; return TOK_INT;}
boolean    { HANDLE_COLUMN; ECHO; return TOK_BOOLEAN;}
function    { HANDLE_COLUMN; ECHO; return TOK_FUNCTION;}
if    { HANDLE_COLUMN; ECHO; return TOK_IF;}
else    { HANDLE_COLUMN; ECHO; return TOK_ELSE;}
while    { HANDLE_COLUMN; ECHO; return TOK_WHILE;}
scanf    { HANDLE_COLUMN; ECHO; return TOK_SCANF;}
printf    { HANDLE_COLUMN; ECHO; return TOK_PRINTF;}
return    { HANDLE_COLUMN; ECHO; return TOK_RETURN;}
"//".*\n ;
" " { HANDLE_COLUMN;}
\n { next_column = 1;}
\t { HANDLE_COLUMN;}
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
"*"    { HANDLE_COLUMN; ECHO; return yytext[0];}

"=="    { HANDLE_COLUMN; ECHO; return TOK_IGUAL;}
"<="    { HANDLE_COLUMN; ECHO; return TOK_MENORIGUAL;}
">="    { HANDLE_COLUMN; ECHO; return TOK_MAYORIGUAL;}
"!="    { HANDLE_COLUMN; ECHO; return TOK_DISTINTO;}
    
"&&"    { HANDLE_COLUMN; ECHO; return TOK_AND;}
"||"    { HANDLE_COLUMN; ECHO; return TOK_OR;}
"!"    { HANDLE_COLUMN; ECHO; return TOK_NOT;}
"<"    { HANDLE_COLUMN; ECHO; return TOK_MENOR;}
">"    { HANDLE_COLUMN; ECHO; return TOK_MAYOR;}
true    { HANDLE_COLUMN; ECHO; yylval.numero = 1; return TOK_TRUE;}
false   { HANDLE_COLUMN; ECHO; yylval.numero = 0; return TOK_FALSE;}
[a-zA-Z][a-zA-Z0-9]*    { if(yyleng>100){
                            emitir_error("identificador demasiado largo"); 
                            return YYerror;
                          }
                           HANDLE_COLUMN; ECHO; 
                           strcpy(yylval.cadena, yytext);
                           return TOK_IDENTIFICADOR;}
[0-9]+    { HANDLE_COLUMN; ECHO; 
            yylval.numero = atoi(yytext);
            return TOK_CONSTANTE_ENTERA;}
. { emitir_error("simbolo no permitido");
    return YYerror;}
%%
void emitir_error(char* cadena_error){
    fprintf(stderr, "****Error en [lin %d, col %d]: %s (%s)\n", yylineno, column+1, cadena_error, yytext);
}

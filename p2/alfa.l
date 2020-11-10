%{
    #include <stdio.h>
    #include <string.h>
    #include "tokens.h"
    int next_column = 1, column = 1;
    #define HANDLE_COLUMN column = next_column; next_column += yyleng
    void emitir_error(char* cadena_error);
%}
%option noyywrap noinput nounput yylineno
%%
main    { HANDLE_COLUMN; return TOK_MAIN;}
int    { HANDLE_COLUMN; return TOK_INT;}
boolean    { HANDLE_COLUMN; return TOK_BOOLEAN;}
array    { HANDLE_COLUMN; return TOK_ARRAY;}
function    { HANDLE_COLUMN; return TOK_FUNCTION;}
if    { HANDLE_COLUMN; return TOK_IF;}
else    { HANDLE_COLUMN; return TOK_ELSE;}
while    { HANDLE_COLUMN; return TOK_WHILE;}
scanf    { HANDLE_COLUMN; return TOK_SCANF;}
printf    { HANDLE_COLUMN; return TOK_PRINTF;}
return    { HANDLE_COLUMN; return TOK_RETURN;}
"set"[ ]+"of"    { HANDLE_COLUMN; return TOK_SETOF;}
"//".*\n ;
" " { HANDLE_COLUMN;}
\n { next_column = 1;}
\t { HANDLE_COLUMN;}
";"    { HANDLE_COLUMN; return TOK_PUNTOYCOMA;}
","    { HANDLE_COLUMN; return TOK_COMA;}
"("    { HANDLE_COLUMN; return TOK_PARENTESISIZQUIERDO;}
")"    { HANDLE_COLUMN; return TOK_PARENTESISDERECHO;}
"["    { HANDLE_COLUMN; return TOK_CORCHETEIZQUIERDO;}
"]"    { HANDLE_COLUMN; return TOK_CORCHETEDERECHO;}
"{"    { HANDLE_COLUMN; return TOK_LLAVEIZQUIERDA;}
"}"    { HANDLE_COLUMN; return TOK_LLAVEDERECHA;}
"=="    { HANDLE_COLUMN; return TOK_IGUAL;}
"<="    { HANDLE_COLUMN; return TOK_MENORIGUAL;}
">="    { HANDLE_COLUMN; return TOK_MAYORIGUAL;}
"!="    { HANDLE_COLUMN; return TOK_DISTINTO;}
"="    { HANDLE_COLUMN; return TOK_ASIGNACION;}
"+"    { HANDLE_COLUMN; return TOK_MAS;}
"-"    { HANDLE_COLUMN; return TOK_MENOS;}
"/"    { HANDLE_COLUMN; return TOK_DIVISION;}
"*"    { HANDLE_COLUMN; return TOK_ASTERISCO;}
"&&"    { HANDLE_COLUMN; return TOK_AND;}
"||"    { HANDLE_COLUMN; return TOK_OR;}
"!"    { HANDLE_COLUMN; return TOK_NOT;}
"<"    { HANDLE_COLUMN; return TOK_MENOR;}
">"    { HANDLE_COLUMN; return TOK_MAYOR;}
true    { HANDLE_COLUMN; return TOK_TRUE;}
false   { HANDLE_COLUMN; return TOK_FALSE;}
[a-zA-Z][a-zA-Z0-9]*    { if(yyleng>100){
                            emitir_error("identificador demasiado largo"); return TOK_ERROR;
                          }
                           HANDLE_COLUMN; return TOK_IDENTIFICADOR;}
[0-9]+    { HANDLE_COLUMN; return TOK_CONSTANTE_ENTERA;}
. { emitir_error("simbolo no permitido"); return TOK_ERROR;}
%%
void emitir_error(char* cadena_error){
    fprintf(stderr, "****Error en [lin %d, col %d]: %s (%s)\n", yylineno, column+1, cadena_error, yytext);
}

int main(int argc, char *argv[]){
    int a;
    if(argc!=3){
      fprintf(stderr, "Numero de argumentos incorrecto, introducir ./alfa ficheroentrada.txt ficherosalida.txt\n");
      return -1;
    }
    yyin = fopen(argv[1], "r");
    if(yyin==NULL){
      fprintf(stderr, "Error abriendo el fichero de entrada\n");
      return -1;
    }
    yyout = fopen(argv[2], "w");
    if(yyout==NULL){
      fprintf(stderr, "Error abriendo el fichero de salida\n");
      return -1;
    }
    for(;a=yylex();){
        if(a==TOK_MAIN) fprintf(yyout, "TOK_MAIN\t%d\t%s\n", TOK_MAIN, yytext);
        else if(a==TOK_INT) fprintf(yyout, "TOK_INT\t%d\t%s\n", TOK_INT, yytext);
        else if(a==TOK_BOOLEAN) fprintf(yyout, "TOK_BOOLEAN\t%d\t%s\n", TOK_BOOLEAN, yytext);
        else if(a==TOK_ARRAY) fprintf(yyout, "TOK_ARRAY\t%d\t%s\n", TOK_ARRAY, yytext);
        else if(a==TOK_FUNCTION) fprintf(yyout, "TOK_FUNCTION\t%d\t%s\n", TOK_FUNCTION, yytext);
        else if(a==TOK_IF) fprintf(yyout, "TOK_IF\t%d\t%s\n", TOK_IF, yytext);
        else if(a==TOK_ELSE) fprintf(yyout, "TOK_ELSE\t%d\t%s\n", TOK_ELSE, yytext);
        else if(a==TOK_WHILE) fprintf(yyout, "TOK_WHILE\t%d\t%s\n", TOK_WHILE, yytext);
        else if(a==TOK_SCANF) fprintf(yyout, "TOK_SCANF\t%d\t%s\n", TOK_SCANF, yytext);
        else if(a==TOK_PRINTF) fprintf(yyout, "TOK_PRINTF\t%d\t%s\n", TOK_PRINTF, yytext);
        else if(a==TOK_RETURN) fprintf(yyout, "TOK_RETURN\t%d\t%s\n", TOK_RETURN, yytext);
        else if(a==TOK_SETOF) fprintf(yyout, "TOK_SETOF\t%d\t%s\n", TOK_SETOF, yytext);
        else if(a==TOK_PUNTOYCOMA) fprintf(yyout, "TOK_PUNTOYCOMA\t%d\t%s\n", TOK_PUNTOYCOMA, yytext);
        else if(a==TOK_COMA) fprintf(yyout, "TOK_COMA\t%d\t%s\n", TOK_COMA, yytext);
        else if(a==TOK_PARENTESISIZQUIERDO) fprintf(yyout, "TOK_PARENTESISIZQUIERDO\t%d\t%s\n", TOK_PARENTESISIZQUIERDO, yytext);
        else if(a==TOK_PARENTESISDERECHO) fprintf(yyout, "TOK_PARENTESISDERECHO\t%d\t%s\n", TOK_PARENTESISDERECHO, yytext);
        else if(a==TOK_CORCHETEIZQUIERDO) fprintf(yyout, "TOK_CORCHETEIZQUIERDO\t%d\t%s\n", TOK_CORCHETEIZQUIERDO, yytext);
        else if(a==TOK_CORCHETEDERECHO) fprintf(yyout, "TOK_CORCHETEDERECHO\t%d\t%s\n", TOK_CORCHETEDERECHO, yytext);
        else if(a==TOK_LLAVEIZQUIERDA) fprintf(yyout, "TOK_LLAVEIZQUIERDA\t%d\t%s\n", TOK_LLAVEIZQUIERDA, yytext);
        else if(a==TOK_LLAVEDERECHA) fprintf(yyout, "TOK_LLAVEDERECHA\t%d\t%s\n", TOK_LLAVEDERECHA, yytext);
        else if(a==TOK_ASIGNACION) fprintf(yyout, "TOK_ASIGNACION\t%d\t%s\n", TOK_ASIGNACION, yytext);
        else if(a==TOK_MAS) fprintf(yyout, "TOK_MAS\t%d\t%s\n", TOK_MAS, yytext);
        else if(a==TOK_MENOS) fprintf(yyout, "TOK_MENOS\t%d\t%s\n", TOK_MENOS, yytext);
        else if(a==TOK_DIVISION) fprintf(yyout, "TOK_DIVISION\t%d\t%s\n", TOK_DIVISION, yytext);
        else if(a==TOK_ASTERISCO) fprintf(yyout, "TOK_ASTERISCO\t%d\t%s\n", TOK_ASTERISCO, yytext);
        else if(a==TOK_AND) fprintf(yyout, "TOK_AND\t%d\t%s\n", TOK_AND, yytext);
        else if(a==TOK_OR) fprintf(yyout, "TOK_OR\t%d\t%s\n", TOK_OR, yytext);
        else if(a==TOK_NOT) fprintf(yyout, "TOK_NOT\t%d\t%s\n", TOK_NOT, yytext);
        else if(a==TOK_IGUAL) fprintf(yyout, "TOK_IGUAL\t%d\t%s\n", TOK_IGUAL, yytext);
        else if(a==TOK_DISTINTO) fprintf(yyout, "TOK_DISTINTO\t%d\t%s\n", TOK_DISTINTO, yytext);
        else if(a==TOK_MENORIGUAL) fprintf(yyout, "TOK_MENORIGUAL\t%d\t%s\n", TOK_MENORIGUAL, yytext);
        else if(a==TOK_MAYORIGUAL) fprintf(yyout, "TOK_MAYORIGUAL\t%d\t%s\n", TOK_MAYORIGUAL, yytext);
        else if(a==TOK_MENOR) fprintf(yyout, "TOK_MENOR\t%d\t%s\n", TOK_MENOR, yytext);
        else if(a==TOK_MAYOR) fprintf(yyout, "TOK_MAYOR\t%d\t%s\n", TOK_MAYOR, yytext);
        else if(a==TOK_IDENTIFICADOR) fprintf(yyout, "TOK_IDENTIFICADOR\t%d\t%s\n", TOK_IDENTIFICADOR, yytext);
        else if(a==TOK_CONSTANTE_ENTERA) fprintf(yyout, "TOK_CONSTANTE_ENTERA\t%d\t%s\n", TOK_CONSTANTE_ENTERA, yytext);
        else if(a==TOK_TRUE) fprintf(yyout, "TOK_TRUE\t%d\t%s\n", TOK_TRUE, yytext);
        else if(a==TOK_FALSE) fprintf(yyout, "TOK_FALSE\t%d\t%s\n", TOK_FALSE, yytext);
        else if(a==TOK_ERROR) break;
    }
}

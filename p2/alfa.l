%{
    #include <stdio.h>
    #include "tokens.h"
%}
%%
main    { return TOK_MAIN;}
int    { return TOK_INT;}
boolean    { return TOK_BOOLEAN;}
array    { return TOK_ARRAY;}
function    { return TOK_FUNCTION;}
if    { return TOK_IF;}
else    { return TOK_ELSE;}
while    { return TOK_WHILE;}
scanf    { return TOK_SCANF;}
printf    { return TOK_PRINTF;}
return    { return TOK_RETURN;}
"set"[]+"of    { return TOK_SETOF;}

";"    { return TOK_PUNTOYCOMA;}
","    { return TOK_COMA;}
"("    { return TOK_PARENTESISIZQUIERDO;}
")"    { return TOK_PARENTESISDERECHO;}
"["    { return TOK_CORCHETEIZQUIERDO;}
"]"    { return TOK_CORCHETEDERECHO;}
"{"    { return TOK_LLAVEIZQUIERDA;}
"}"    { return TOK_LLAVEDERECHA;}
"="    { return TOK_ASIGNACION;}
"+"    { return TOK_MAS;}
"-"    { return TOK_MENOS;}
"/"    { return TOK_DIVISION;}
"*"    { return TOK_ASTERISCO;}
&&    { return TOK_AND;}
||    { return TOK_OR;}
"!"    { return TOK_NOT;}
"=="    { return TOK_IGUAL;}
"!="    { return TOK_DISTINTO;}
"<="    { return TOK_MENORIGUAL;}
>=    { return TOK_MAYORIGUAL;}
<    { return TOK_MENOR;}
>    { return TOK_MAYOR;}

[a-zA-Z][a-zA-Z0-9]*    { return TOK_IDENTIFICADOR;} 
[0-9]+    { return TOK_CONSTANTE_ENTERA;}
true    { return TOK_TRUE;}
false    { return TOK_FALSE;}

"//"[ ]\n ;
" " ;
\n ;
. { return TOK_ERROR;}
%%

int main(){
    int a;
    for(;a=yylex();){
        if(a==TOK_MAIN) printf("TOK_MAIN %s\n", yytext);
        else if(a==TOK_INT) printf("TOK_INT %s\n", yytext);
        else if(a==TOK_BOOLEAN) printf("TOK_BOOLEAN %s\n", yytext);
        else if(a==TOK_ARRAY) printf("TOK_ARRAY %s\n", yytext);
        else if(a==TOK_FUNCTION) printf("TOK_FUNCTION %s\n", yytext);
        else if(a==TOK_IF) printf("TOK_IF %s\n", yytext);
        else if(a==TOK_ELSE) printf("TOK_ELSE %s\n", yytext);
        else if(a==TOK_WHILE) printf("TOK_WHILE %s\n", yytext);
        else if(a==TOK_SCANF) printf("TOK_SCANF %s\n", yytext);
        else if(a==TOK_PRINTF) printf("TOK_PRINTF %s\n", yytext);
        else if(a==TOK_RETURN) printf("TOK_RETURN %s\n", yytext);
        else if(a==TOK_SETOF) printf("TOK_SETOF %s\n", yytext);
        else if(a==TOK_PUNTOYCOMA) printf("TOK_PUNTOYCOMA %s\n", yytext);
        else if(a==TOK_COMA) printf("TOK_COMA %s\n", yytext);
        else if(a==TOK_PARENTESISIZQUIERDO) printf("TOK_PARENTESISIZQUIERDO %s\n", yytext);
        else if(a==TOK_PARENTESISIZQUIERDO) printf("TOK_PARENTESISIZQUIERDO %s\n", yytext);
        else if(a==TOK_PARENTESISDERECHO) printf("TOK_PARENTESISDERECHO %s\n", yytext);
        else if(a==TOK_CORCHETEIZQUIERDO) printf("TOK_CORCHETEIZQUIERDO %s\n", yytext);
        else if(a==TOK_CORCHETEDERECHO) printf("TOK_CORCHETEDERECHO %s\n", yytext);
        else if(a==TOK_LLAVEIZQUIERDA) printf("TOK_LLAVEIZQUIERDA %s\n", yytext);
        else if(a==TOK_LLAVEDERECHA) printf("TOK_LLAVEDERECHA %s\n", yytext);
        else if(a==TOK_ASIGNACION) printf("TOK_ASIGNACION %s\n", yytext);
        else if(a==TOK_MAS) printf("TOK_MAS %s\n", yytext);
        else if(a==TOK_MENOS) printf("TOK_MENOS %s\n", yytext);
        else if(a==TOK_DIVISION) printf("TOK_DIVISION %s\n", yytext);
        else if(a==TOK_ASTERISCO) printf("TOK_ASTERISCO %s\n", yytext);
        else if(a==TOK_AND) printf("TOK_AND %s\n", yytext);
        else if(a==TOK_OR) printf("TOK_OR %s\n", yytext);
        else if(a==TOK_NOT) printf("TOK_NOT %s\n", yytext);
        else if(a==TOK_IGUAL) printf("TOK_IGUAL %s\n", yytext);
        else if(a==TOK_DISTINTO) printf("TOK_DISTINTO %s\n", yytext);
        else if(a==TOK_MENORIGUAL) printf("TOK_MENORIGUAL %s\n", yytext);
        else if(a==TOK_MAYORIGUAL) printf("TOK_MAYORIGUAL %s\n", yytext);
        else if(a==TOK_MENOR) printf("TOK_MENOR %s\n", yytext);
        else if(a==TOK_MAYOR) printf("TOK_MAYOR %s\n", yytext);
        else if(a==TOK_IDENTIFICADOR) printf("TOK_IDENTIFICADOR %s\n", yytext);
        else if(a==TOK_CONSTANTE_ENTERA) printf("TOK_CONSTANTE_ENTERA %s\n", yytext);
        else if(a==TOK_TRUE) printf("TOK_TRUE %s\n", yytext);
        else if(a==TOK_FALSE) printf("TOK_FALSE %s\n", yytext);
        else if(a==TOK_ERROR) printf("TOK_ERROR %s\n", yytext);

    }
}
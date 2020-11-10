%{
    #include <stdio.h>
%}
%option noyywrap
%%
main    { return 1;}
function    { return 2;}
%%

int main(int argc, char *argv[]){
    int a;
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    for(;a=yylex();){
        if(a==1) fprintf(yyout, "TOK_MAIN %s\n", yytext);
        else if(a==2) fprintf(yyout, "TOK_FUNCTION %s\n", yytext);
    }
}

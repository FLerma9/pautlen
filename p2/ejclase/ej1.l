%{
    #include <stdio.h>
%}
%%
main    { return 1;}
function    { return 2;}
%%

int main(){
    int a;
    for(;a=yylex();){
        if(a==1) printf("TOK_MAIN %s\n", yytext);
        else if(a==2) printf("TOK_FUNCTION %s\n", yytext);
    }
}
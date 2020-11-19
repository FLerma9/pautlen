%{
%}

%union
{
    char* cadena;
    int numero;
}

%token TOK_MAIN, TOK_INT, TOK_BOOLEAN, TOK_IDENTIFICADOR

%%
programa        :   TOK_MAIN '{' declaraciones '}'
declaraciones   :   declaracion 
                | declaracion declaraciones
declaracion     :   clase identificadores
clase           :   clase_escalar
clase_escalar   :   tipo
tipo            :   TOK_INT
                |   TOK_BOOLEAN
identificadores :   id 
                |   id ',' identificadores
id   :   TOK_IDENTIFICADOR   {put_in_symbol_table(yylval.id);}

%%
int main(){
    return yyparse();
}
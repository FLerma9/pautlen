%{
%}

%union
{
    char* cadena;
    int numero;
}

%token TOK_MAIN, TOK_INT, TOK_BOOLEAN, TOK_IDENTIFICADOR

%token TOK_MAS, TOK_MENOS, TOK_ASTERISCO, TOK_DIVISION

%token TOK_AND, TOK_OR, TOK_NOT, TOK_TRUE, TOK_FALSE
%token TOK_IGUAL, TOK_DISTINTO, TOK_MENORIGUAL, TOK_MAYORIGUAL, TOK_MENOR, TOK_MAYOR

%token TOK_CONSTANTE_ENTERA
%token TOK_PARENTESISDERECHO, TOK_PARENTESISIZQUIERDO

%left TOK_MAS TOK_MENOS
%left TOK_ASTERISCO TOK_DIVISION

%%
programa        :   TOK_MAIN TOK_PARENTESISIZQUIERDO declaraciones TOK_PARENTESISDERECHO
declaraciones   :   declaracion 
                | declaracion declaraciones
declaracion     :   clase identificadores
clase           :   clase_escalar
clase_escalar   :   tipo
tipo            :   TOK_INT
                |   TOK_BOOLEAN
identificadores :   identificador 
                |   identificador ',' identificadores
identificador   :   TOK_IDENTIFICADOR   {put_in_symbol_table(yylval.id);}
exp             : exp TOK_MAS exp
                | exp TOK_MENOS exp
                | exp TOK_DIVISION exp
                | exp TOK_ASTERISCO exp
                | TOK_MENOS exp
                | exp TOK_AND exp
                | exp TOK_OR exp
                | TOK_NOT exp
                | identificador
                | constante
                | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO
                | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO
    
constante       : constante_logica
                | constante_entera
          
constante_logica : TOK_TRUE | TOK_FALSE

constante_entera : TOK_CONSTANTE_ENTERA

comparacion     : exp TOK_IGUAL exp
                | exp TOK_DISTINTO exp
                | exp TOK_MENORIGUAL exp
                | exp TOK_MAYORIGUAL exp
                | exp TOK_MENOR exp
                | exp TOK_MAYOR exp

%%
int main(){
    return yyparse();
}
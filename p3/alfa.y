%{
    #include <stdio.h>
    #include "flexbison.h"
    #define YYERROR_VERBOSE 1
    int yylex();
    #define YYDEBUG 1
    
%}

%union
{
    char cadena[100];
    int numero;
}

%token TOK_MAIN TOK_INT TOK_BOOLEAN 
%token TOK_SCANF TOK_PRINTF TOK_FUNCTION TOK_RETURN
%token TOK_IF TOK_ELSE TOK_WHILE

%token TOK_AND TOK_OR TOK_NOT 
%token TOK_IGUAL TOK_DISTINTO TOK_MENORIGUAL TOK_MAYORIGUAL TOK_MENOR TOK_MAYOR
%token TOK_LLAVEIZQUIERDA TOK_LLAVEDERECHA
%token TOK_PARENTESISIZQUIERDO TOK_PARENTESISDERECHO
%token <numero> TOK_CONSTANTE_ENTERA TOK_TRUE TOK_FALSE
%token <cadena> TOK_IDENTIFICADOR

%left '+' '-' TOK_OR
%left '*' '/' TOK_AND
%nonassoc UMINUS

%type <numero> exp comparacion constante constante_logica constante_entera

%start programa

%%
programa        :   TOK_MAIN '{' declaraciones funciones sentencias '}'

declaraciones   :   declaracion 
                |   declaracion declaraciones
declaracion     :   clase identificadores ';'

clase           :   clase_escalar
clase_escalar   :   tipo
tipo            :   TOK_INT
                |   TOK_BOOLEAN
identificadores :   identificador
                |   identificador ',' identificadores

funciones       :   funcion funciones
                |
funcion         :   TOK_FUNCTION tipo identificador 
                    '(' parametros_funcion ')' '{' declaraciones_funcion sentencias '}'
parametros_funcion  :   parametro_funcion resto_parametros_funcion
                    |
resto_parametros_funcion    :   ';' parametro_funcion resto_parametros_funcion
                            |
parametro_funcion   :   tipo identificador
declaraciones_funcion       :   declaraciones
                            |

sentencias      :   sentencia 
                |   sentencia sentencias
sentencia       :   sentencia_simple ';'
                |   bloque
sentencia_simple    :   asignacion
                    |   lectura
                    |   escritura
                    |   retorno_funcion

bloque          :   condicional
                |   bucle

asignacion      :   identificador '=' exp

condicional     :   TOK_IF '(' exp ')' '{' sentencias '}'
                |   TOK_IF '(' exp ')' '{' sentencias '}' TOK_ELSE '{' sentencias '}'

bucle           :   TOK_WHILE '(' exp ')' '{' sentencias '}'

lectura         :   TOK_SCANF identificador
escritura       :   TOK_PRINTF exp
retorno_funcion :   TOK_RETURN exp

exp             :   exp '+' exp     {$$ = $1 + $3;}
                |   exp '-' exp   {$$ = $1 - $3;}
                |   exp '/' exp    {$$ = $1 / $3;}    
                |   exp '*' exp   {$$ = $1 * $3;}
                |   '-' exp %prec UMINUS{$$ = - $2;}
                |   exp TOK_AND exp     {$$ = $1 && $3;} 
                |   exp TOK_OR exp      {$$ = $1 || $3;}
                |   TOK_NOT exp %prec UMINUS{$$ = ! $2;}
                |   identificador       {$$ = 0;}
                |   constante
                |   '(' exp ')'   {$$ = $2;}
                |   '(' comparacion ')'   {$$ = $2;}    

comparacion     :   exp TOK_IGUAL exp       {$$ = $1 == $3;}
                |   exp TOK_DISTINTO exp    {$$ = $1 != $3;}
                |   exp TOK_MENORIGUAL exp  {$$ = $1 <= $3;}
                |   exp TOK_MAYORIGUAL exp  {$$ = $1 >= $3;}
                |   exp TOK_MENOR exp       {$$ = $1 < $3;}
                |   exp TOK_MAYOR exp       {$$ = $1 > $3;}

constante       :   constante_logica {$$ = $1;}
                |   constante_entera {$$ = $1;}
          
constante_logica    :   TOK_TRUE {$$ = $1;}
                    |   TOK_FALSE {$$ = $1;}

constante_entera :  TOK_CONSTANTE_ENTERA {$$ = $1;}

identificador   :   TOK_IDENTIFICADOR 

%%

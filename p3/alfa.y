%{
    #include <stdio.h>
    #include "pruebaSintactico.h"
    #define YYERROR_VERBOSE 1
    #define ECHOYYPARSE(rulenum, text) fprintf(yyout, ";R%d:\t%s\n", rulenum, text)
    int yylex();
%}

%union
{
    char cadena[100];
    int numero;
}

%token TOK_MAIN 
%token TOK_SCANF TOK_PRINTF TOK_FUNCTION TOK_RETURN
%token TOK_IF TOK_ELSE TOK_WHILE

%token TOK_INT TOK_BOOLEAN TOK_ARRAY
%token TOK_AND TOK_OR TOK_NOT 
%token TOK_IGUAL TOK_DISTINTO TOK_MENORIGUAL TOK_MAYORIGUAL TOK_MENOR TOK_MAYOR
%token <numero> TOK_CONSTANTE_ENTERA TOK_TRUE TOK_FALSE
%token <cadena> TOK_IDENTIFICADOR

%left '+' '-' TOK_OR
%left '*' '/' TOK_AND
%nonassoc UMINUS

%type <numero> elemento_vector exp comparacion constante constante_logica constante_entera

%start programa

%%
programa        :   TOK_MAIN '{' declaraciones funciones sentencias '}'
    {ECHOYYPARSE(1, "<programa> ::= main { <declaraciones> <funciones> <sentencias> }");}  

declaraciones   :   declaracion 
    {ECHOYYPARSE(2, "<declaraciones> ::= <declaracion>");}
                |   declaracion declaraciones 
    {ECHOYYPARSE(3, "<declaraciones> ::= <declaracion> <declaraciones>");}
declaracion     :   clase identificadores ';' 
    {ECHOYYPARSE(4, "<declaracion> ::= <clase> <identificadores> ;");}
clase           :   clase_escalar   {ECHOYYPARSE(5, "<clase> ::= <clase_escalar>");}
                |   clase_vector    {ECHOYYPARSE(7, "<clase> ::= <clase_vector>");}

clase_escalar   :   tipo    
    {ECHOYYPARSE(9, "<clase_escalar> ::= <tipo>");}
tipo            :   TOK_INT         {ECHOYYPARSE(10, "<tipo> ::= int");}
                |   TOK_BOOLEAN     {ECHOYYPARSE(11, "<tipo> ::= boolean");}

clase_vector    :   TOK_ARRAY tipo '[' constante_entera ']'   
    {ECHOYYPARSE(15, "<clase_vector> ::= TOK_ARRAY <tipo> [ <constante_entera> ]");}

identificadores :   identificador   
    {ECHOYYPARSE(18, "<identificadores> ::= <identificador>");}
                |   identificador ',' identificadores 
    {ECHOYYPARSE(19, "<identificadores> ::= <identificador> , <identificadores>");}

funciones       :   funcion funciones   {ECHOYYPARSE(20, "<funciones> ::= <funcion> <funciones>");}
                |                       {ECHOYYPARSE(21, "<funciones> ::= ");}
funcion         :   TOK_FUNCTION tipo identificador     
                    '(' parametros_funcion ')' '{' declaraciones_funcion sentencias '}'
    {ECHOYYPARSE(22, "<funcion> ::= function <tipo> <identificador> ( <parametro_funcion> ) { <declaraciones_funcion> <sentencias> }");}
parametros_funcion  :   parametro_funcion resto_parametros_funcion
    {ECHOYYPARSE(23, "<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
                    |   
    {ECHOYYPARSE(24, "<parametros_funcion> ::= ");}
resto_parametros_funcion    :   ';' parametro_funcion resto_parametros_funcion
    {ECHOYYPARSE(25, "<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>");}
                            |   
    {ECHOYYPARSE(26, "<resto_parametros_funcion> ::= ");}
parametro_funcion   :   tipo identificador  {ECHOYYPARSE(27, "<parametro_funcion> ::= <tipo> <identificador>");}
declaraciones_funcion       :   declaraciones   
    {ECHOYYPARSE(28, "<declaraciones_funcion> ::= <identificador> <identificador>");}
                            |                   
    {ECHOYYPARSE(29, "<declaraciones_funcion> ::= ");}

sentencias      :   sentencia               {ECHOYYPARSE(30, "<sentencias> ::= <sentencia>");}
                |   sentencia sentencias    {ECHOYYPARSE(31, "<sentencias> ::= <sentencia> <sentencias>");}
sentencia       :   sentencia_simple ';'    {ECHOYYPARSE(32, "<sentencia> ::= <sentencia_simple> ;");}
                |   bloque                  {ECHOYYPARSE(33, "<sentencia> ::= <bloque>");}
sentencia_simple    :   asignacion          {ECHOYYPARSE(34, "<sentencia_simple> ::= <asignacion>");}
                    |   lectura             {ECHOYYPARSE(35, "<sentencia_simple> ::= <lectura>");}
                    |   escritura           {ECHOYYPARSE(36, "<sentencia_simple> ::= <escritura>");}
                    |   retorno_funcion     {ECHOYYPARSE(37, "<sentencia_simple> ::= <retorno_funcion>");}

bloque          :   condicional             {ECHOYYPARSE(40, "<bloque> ::= <condicional>");}
                |   bucle                   {ECHOYYPARSE(41, "<bloque> ::= <bucle>");}

asignacion      :   identificador '=' exp   {ECHOYYPARSE(43, "<asignacion> ::= <identificador> = <exp>");}
                |   elemento_vector '=' exp {ECHOYYPARSE(44, "<asignacion> ::= <elemento_vector> = <exp>");} 

elemento_vector :   identificador '[' exp ']'   
    {ECHOYYPARSE(48, "<elemento_vector> ::= <identificador> [ <exp> ]");}

condicional     :   TOK_IF '(' exp ')' '{' sentencias '}'
    {ECHOYYPARSE(50, "<condicional> ::= if ( <exp> ) { <sentencias> }");}
                |   TOK_IF '(' exp ')' '{' sentencias '}' TOK_ELSE '{' sentencias '}'
    {ECHOYYPARSE(51, "<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");}
bucle           :   TOK_WHILE '(' exp ')' '{' sentencias '}'
    {ECHOYYPARSE(52, "<bucle> ::= while ( <exp> ) { <sentencias> }");}

lectura         :   TOK_SCANF identificador {ECHOYYPARSE(54, "<lectura> ::= scanf <identificador>");}
escritura       :   TOK_PRINTF exp          {ECHOYYPARSE(56, "<escritura> ::= printf <exp>");}
retorno_funcion :   TOK_RETURN exp          {ECHOYYPARSE(61, "<retorno_funcion> ::= return <exp>");}

exp             :   exp '+' exp     {$$ = $1 + $3; ECHOYYPARSE(72, "<exp> ::= <exp> + <exp>");}
                |   exp '-' exp   {$$ = $1 - $3; ECHOYYPARSE(73, "<exp> ::= <exp> - <exp>");}
                |   exp '/' exp    {$$ = $1 / $3; ECHOYYPARSE(74, "<exp> ::= <exp> / <exp>");}    
                |   exp '*' exp   {$$ = $1 * $3; ECHOYYPARSE(75, "<exp> ::= <exp> * <exp>");}
                |   '-' exp %prec UMINUS{$$ = - $2; ECHOYYPARSE(76, "<exp> ::= - <exp>");}
                |   exp TOK_AND exp     {$$ = $1 && $3; ECHOYYPARSE(77, "<exp> ::= <exp> && <exp>");} 
                |   exp TOK_OR exp      {$$ = $1 || $3; ECHOYYPARSE(78, "<exp> ::= <exp> || <exp>");}
                |   TOK_NOT exp %prec UMINUS{$$ = ! $2; ECHOYYPARSE(79, "<exp> ::= ! <exp>");}
                |   identificador       {ECHOYYPARSE(80, "<exp> ::= <identificador>");}
                |   constante           {ECHOYYPARSE(81, "<exp> ::= <constante>");}
                |   '(' exp ')'         {$$ = $2; ECHOYYPARSE(82, "<exp> ::= ( <exp> )");}
                |   '(' comparacion ')' {$$ = $2; ECHOYYPARSE(83, "<exp> ::= ( <comparacion> )");}
                |   elemento_vector     {ECHOYYPARSE(85, "<exp> ::= <elemento_vector>");}
                |   identificador '(' lista_expresiones ')' 
    {ECHOYYPARSE(88, "<exp> ::= <identificador> ( <lista_expresiones> )");}

lista_expresiones       :   exp resto_lista_expresiones 
    {ECHOYYPARSE(89, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
                        |
    {ECHOYYPARSE(90, "<lista_expresiones> ::= ");}
resto_lista_expresiones :   ',' exp resto_lista_expresiones 
    {ECHOYYPARSE(91, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
                        |
    {ECHOYYPARSE(92, "<resto_lista_expresiones> ::= ");}

comparacion     :   exp TOK_IGUAL exp       {$$ = $1 == $3; ECHOYYPARSE(93, "<exp> ::= <exp> == <exp>");}
                |   exp TOK_DISTINTO exp    {$$ = $1 != $3; ECHOYYPARSE(94, "<exp> ::= <exp> != <exp>");}
                |   exp TOK_MENORIGUAL exp  {$$ = $1 <= $3; ECHOYYPARSE(95, "<exp> ::= <exp> <= <exp>");}
                |   exp TOK_MAYORIGUAL exp  {$$ = $1 >= $3; ECHOYYPARSE(96, "<exp> ::= <exp> >= <exp>");}
                |   exp TOK_MENOR exp       {$$ = $1 < $3; ECHOYYPARSE(97, "<exp> ::= <exp> < <exp>");}
                |   exp TOK_MAYOR exp       {$$ = $1 > $3; ECHOYYPARSE(98, "<exp> ::= <exp> > <exp>");}

constante       :   constante_logica {ECHOYYPARSE(99, "<constante> ::= <constante_logica>");}
                |   constante_entera {ECHOYYPARSE(100, "<constante> ::= <constante_entera>");}
          
constante_logica    :   TOK_TRUE {ECHOYYPARSE(102, "<constante_logica> ::= true");}
                    |   TOK_FALSE {ECHOYYPARSE(103, "<constante_logica> ::= false");}

constante_entera :  TOK_CONSTANTE_ENTERA    {ECHOYYPARSE(104, "<constante_entera> ::= numero");}

identificador   :   TOK_IDENTIFICADOR       {ECHOYYPARSE(108, "<identificador> ::= TOK_IDENTIFICADOR");}

%%

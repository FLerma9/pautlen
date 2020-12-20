%{
    #include <stdio.h>
    #include "alfa.h"
    #include "tablasimbolos.h"
    #include "generacion.h"
    #include "string.h"
    #define ECHOYYPARSE(rulenum, text) fprintf(stdout, ";R%d:\t%s\n", rulenum, text)
    int yylex();
    tabla_simbolos *tsymb;

    int categoria_actual;
    int tipo_actual;
    int clase_actual;
    int tamano_actual;
    int posicion_actual;
    int etiqueta_actual=0;

    int mismo_tipo(int tipo, int op1tipo, int op2tipo);
    void escribir_aux(informacion info);
    void ejecutar_operacion(int op, informacion info1, informacion info2);
%}
%union
{
    informacion atrib;
}

%token TOK_MAIN
%token TOK_SCANF TOK_PRINTF TOK_FUNCTION TOK_RETURN
%token TOK_IF TOK_ELSE TOK_WHILE

%token TOK_INT TOK_BOOLEAN TOK_ARRAY
%token TOK_AND TOK_OR TOK_NOT
%token TOK_IGUAL TOK_DISTINTO TOK_MENORIGUAL TOK_MAYORIGUAL TOK_MENOR TOK_MAYOR
%token <atrib> TOK_CONSTANTE_ENTERA TOK_TRUE TOK_FALSE
%token <atrib> TOK_IDENTIFICADOR

%left '+' '-' TOK_OR
%left '*' '/' TOK_AND
%nonassoc UMINUS

%type <atrib> elemento_vector exp comparacion constante constante_logica constante_entera
%start programa

%%
programa        :  {tsymb = create_tabla_simbolos();}
    TOK_MAIN '{' {escribir_cabecera_bss(yyout); categoria_actual = VARIABLE; /*CAMBIAR CUANDO FUNCIONES*/}
    declaraciones  {escribir_subseccion_data(yyout); escribir_segmento_codigo(yyout);}
    funciones {escribir_inicio_main(yyout);}
    sentencias '}' {escribir_fin(yyout);destroy_tabla_simbolos(tsymb);}
    {ECHOYYPARSE(1, "<programa> ::= main { <declaraciones> <funciones> <sentencias> }");}

declaraciones   :   declaracion
    {ECHOYYPARSE(2, "<declaraciones> ::= <declaracion>");}
                |   declaracion declaraciones
    {ECHOYYPARSE(3, "<declaraciones> ::= <declaracion> <declaraciones>");}
declaracion     :   clase identificadores ';'
    {ECHOYYPARSE(4, "<declaracion> ::= <clase> <identificadores> ;");}
clase           :   clase_escalar   {clase_actual=ESCALAR; ECHOYYPARSE(5, "<clase> ::= <clase_escalar>");}
                |   clase_vector    {clase_actual=VECTOR; ECHOYYPARSE(7, "<clase> ::= <clase_vector>");}

clase_escalar   :   tipo
                    {
                        tamano_actual = 1;
                        ECHOYYPARSE(9, "<clase_escalar> ::= <tipo>");
                    }
tipo            :   TOK_INT         {tipo_actual=INT ;ECHOYYPARSE(10, "<tipo> ::= int");}
                |   TOK_BOOLEAN     {tipo_actual=BOOLEAN; ECHOYYPARSE(11, "<tipo> ::= boolean");}

clase_vector    :   TOK_ARRAY tipo '[' TOK_CONSTANTE_ENTERA ']'
                    {
                        if($4.valor_entero < 0 || $4.valor_entero>MAX_VECTOR)
                            return error_sem(size_v, NULL);
                        tamano_actual = $4.valor_entero;
                    }

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

asignacion      :   TOK_IDENTIFICADOR '=' exp   {informacion *i = buscar_identificador(tsymb, $1.identificador);
                                                if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                                else if (i->tipo != $3.tipo) return error_sem(incomp_assgn, NULL);
                                                asignar(yyout, $1.identificador, $3.es_direccion);
                                                ECHOYYPARSE(43, "<asignacion> ::= <TOK_IDENTIFICADOR> = <exp>");}
                |   elemento_vector '=' exp {if ($1.tipo != $3.tipo) return error_sem(incomp_assgn, NULL);
                                            asignarElementoVector(yyout, $3.es_direccion);
                                            ECHOYYPARSE(44, "<asignacion> ::= <elemento_vector> = <exp>");}

elemento_vector :   TOK_IDENTIFICADOR '[' exp ']'{if($3.tipo != ENTERO) return error_sem(index_noint, NULL);
                                                  informacion *i = buscar_identificador(tsymb, $1.identificador);
                                                  if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                                  else if (i->categoria == FUNCION) return 1;
                                                  else if (i->clase != VECTOR) return error_sem(index_in_nov, $1.identificador);
                                                  $$.tipo = i->tipo;
                                                  $$.es_direccion = 1;
                                                  escribir_elemento_vector(yyout, $1.identificador, i->tamano, $3.es_direccion);
                                                  ECHOYYPARSE(48, "<elemento_vector> ::= <TOK_IDENTIFICADOR> [ <exp> ]");}

condicional     :   if_cond ')' '{' sentencias '}'
    {ECHOYYPARSE(50, "<condicional> ::= if ( <exp> ) { <sentencias> }");}
                |   if_then TOK_ELSE '{' sentencias '}' {}
    {ECHOYYPARSE(51, "<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");}
if_cond         :   TOK_IF '(' exp {}
if_then         :   if_cond ')' '{' sentencias '}' {}
bucle           :   TOK_WHILE '(' exp ')' '{' sentencias '}'
    {ECHOYYPARSE(52, "<bucle> ::= while ( <exp> ) { <sentencias> }");}

lectura         :   TOK_SCANF TOK_IDENTIFICADOR {
                                                informacion *i = buscar_identificador(tsymb, $2.identificador);
                                                if (i == NULL) return error_sem(undec_acc, $2.identificador);
                                                else if (i->categoria == FUNCION) return 1;
                                                else if (i->clase == VECTOR) return 1;
                                                leer(yyout, i->identificador, i->tipo);
                                                ECHOYYPARSE(54, "<lectura> ::= scanf <TOK_IDENTIFICADOR>");}
escritura       :   TOK_PRINTF exp  {escribir(yyout, $2.es_direccion, $2.tipo);
                                    ECHOYYPARSE(56, "<escritura> ::= printf <exp>");}
retorno_funcion :   TOK_RETURN exp          {ECHOYYPARSE(61, "<retorno_funcion> ::= return <exp>");}

exp             :   exp '+' exp {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(arit_bool, NULL);
                                else {
                                    $$.tipo = INT;
                                    $$.es_direccion = 0;
                                    ejecutar_operacion(SUMA, $1, $3);
                                    ECHOYYPARSE(72, "<exp> ::= <exp> + <exp>");
                                    }
                                }
                |   exp '-' exp {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(arit_bool, NULL);
                                else {
                                    $$.tipo = INT;
                                    $$.es_direccion = 0;
                                    ejecutar_operacion(RESTA, $1, $3);
                                    ECHOYYPARSE(73, "<exp> ::= <exp> - <exp>");
                                    }
                                }
                |   exp '/' exp {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(arit_bool, NULL);
                                else {
                                    $$.tipo = INT;
                                    $$.es_direccion = 0;
                                    ejecutar_operacion(DIVISION, $1, $3);
                                    ECHOYYPARSE(74, "<exp> ::= <exp> / <exp>");
                                    }
                                }
                |   exp '*' exp {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(arit_bool, NULL);
                                else {
                                    $$.tipo = INT;
                                    $$.es_direccion = 0;
                                    ejecutar_operacion(MULTIPLICACION, $1, $3);
                                    ECHOYYPARSE(75, "<exp> ::= <exp> * <exp>");
                                    }
                                }
                |   '-' exp %prec UMINUS{if($2.tipo!=INT) return error_sem(arit_bool, NULL);
                                        else{
                                            $$.tipo = INT;
                                            $$.es_direccion = 0;
                                            ejecutar_operacion(CAMBIO_SIGNO, $2, $2);
                                            ECHOYYPARSE(76, "<exp> ::= - <exp>");
                                            }
                                        }
                |   exp TOK_AND exp     {if(!mismo_tipo(BOOLEAN, $1.tipo, $3.tipo)) return error_sem(log_int, NULL);
                                         else{
                                           $$.tipo = BOOLEAN;
                                           $$.es_direccion = 0;
                                           ejecutar_operacion(AND, $1, $3);
                                         }
                                         ECHOYYPARSE(77, "<exp> ::= <exp> && <exp>");}
                |   exp TOK_OR exp      {if(!mismo_tipo(BOOLEAN, $1.tipo, $3.tipo)) return error_sem(log_int, NULL);
                                        else{
                                          $$.tipo = BOOLEAN;
                                          $$.es_direccion = 0;
                                          ejecutar_operacion(OR, $1, $3);
                                        }
                                        ECHOYYPARSE(78, "<exp> ::= <exp> || <exp>");}
                |   TOK_NOT exp %prec UMINUS{if($2.tipo != BOOLEAN) return error_sem(log_int, NULL);
                                            else{
                                              $$.tipo = BOOLEAN;
                                              $$.es_direccion = 0;
                                              no(yyout, $2.es_direccion, etiqueta_actual);
                                              etiqueta_actual+=1; // TODO CHECK
                                            }
                                            ECHOYYPARSE(79, "<exp> ::= ! <exp>");}
                |   TOK_IDENTIFICADOR   {
                                        informacion *i = buscar_identificador(tsymb, $1.identificador);
                                        if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                        else if (i->categoria == FUNCION) return error_sem(inc_num_pam, $1.identificador);
                                        else if (i->clase == VECTOR) return 1;
                                        strcpy($$.identificador, $1.identificador);
                                        $$.tipo = i->tipo;
                                        $$.es_direccion = 1;
                                        escribir_aux($$);
                                        ECHOYYPARSE(80, "<exp> ::= <TOK_IDENTIFICADOR>");
                                        }
                |   constante           {$$.tipo = $1.tipo; $$.es_direccion = 0; $$.valor_entero = $1.valor_entero;
                                        escribir_aux($$);
                                        ECHOYYPARSE(81, "<exp> ::= <constante>");}
                |   '(' exp ')'         {$$.tipo = $2.tipo; $$.es_direccion = $2.es_direccion; $$.valor_entero = $2.valor_entero;
                                        ECHOYYPARSE(82, "<exp> ::= ( <exp> )");}
                |   '(' comparacion ')' {$$.tipo = BOOLEAN; $$.es_direccion = 0; $$.valor_entero = $2.valor_entero;
                                        //escribir_aux($$);
                                        ECHOYYPARSE(83, "<exp> ::= ( <comparacion> )");}
                |   elemento_vector     {$$.tipo = $1.tipo; $$.es_direccion = 1;
                                        ECHOYYPARSE(85, "<exp> ::= <elemento_vector>");}
                |   TOK_IDENTIFICADOR '(' lista_expresiones ')'
    {ECHOYYPARSE(88, "<exp> ::= <TOK_IDENTIFICADOR> ( <lista_expresiones> )");}

lista_expresiones       :   exp resto_lista_expresiones
    {ECHOYYPARSE(89, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
                        |
    {ECHOYYPARSE(90, "<lista_expresiones> ::= ");}
resto_lista_expresiones :   ',' exp resto_lista_expresiones
    {ECHOYYPARSE(91, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
                        |
    {ECHOYYPARSE(92, "<resto_lista_expresiones> ::= ");}

comparacion     :   exp TOK_IGUAL exp       {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(comp_bool, NULL);
                                            else{
                                              $$.tipo = BOOLEAN;
                                              $$.es_direccion = 0;
                                              ejecutar_operacion(IGUAL, $1, $3);
                                              ECHOYYPARSE(93, "<exp> ::= <exp> == <exp>");
                                              }
                                            }
                |   exp TOK_DISTINTO exp    {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(comp_bool, NULL);
                                            else{
                                              $$.tipo = BOOLEAN;
                                              $$.es_direccion = 0;
                                              ejecutar_operacion(DISTINTO, $1, $3);
                                              ECHOYYPARSE(94, "<exp> ::= <exp> != <exp>");
                                              }
                                            }
                |   exp TOK_MENORIGUAL exp  {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(comp_bool, NULL);
                                            else{
                                              $$.tipo = BOOLEAN;
                                              $$.es_direccion = 0;
                                              ejecutar_operacion(MENORIGUAL, $1, $3);
                                              ECHOYYPARSE(95, "<exp> ::= <exp> <= <exp>");
                                              }
                                            }
                |   exp TOK_MAYORIGUAL exp  {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(comp_bool, NULL);
                                            else{
                                              $$.tipo = BOOLEAN;
                                              $$.es_direccion = 0;
                                              ejecutar_operacion(MAYORIGUAL, $1, $3);
                                              ECHOYYPARSE(96, "<exp> ::= <exp> >= <exp>");
                                              }
                                            }
                |   exp TOK_MENOR exp       {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(comp_bool, NULL);
                                            else{
                                              $$.tipo = BOOLEAN;
                                              $$.es_direccion = 0;
                                              ejecutar_operacion(MENOR, $1, $3);
                                              ECHOYYPARSE(97, "<exp> ::= <exp> < <exp>");
                                              }
                                            }
                |   exp TOK_MAYOR exp       {if(!mismo_tipo(INT, $1.tipo, $3.tipo)) return error_sem(comp_bool, NULL);
                                            else{
                                              $$.tipo = BOOLEAN;
                                              $$.es_direccion = 0;
                                              ejecutar_operacion(MAYOR, $1, $3);
                                              ECHOYYPARSE(98, "<exp> ::= <exp> > <exp>");
                                              }
                                            }

constante       :   constante_logica {$$.tipo = BOOLEAN; $$.es_direccion = 0; $$.valor_entero = $1.valor_entero; /* TODO CHECK*/ ECHOYYPARSE(99, "<constante> ::= <constante_logica>");}
                |   constante_entera {$$.tipo = INT; $$.es_direccion = 0; $$.valor_entero = $1.valor_entero; ECHOYYPARSE(100, "<constante> ::= <constante_entera>");}

constante_logica    :   TOK_TRUE {$$.valor_entero = $1.valor_entero; ECHOYYPARSE(102, "<constante_logica> ::= true");}
                    |   TOK_FALSE {$$.valor_entero = $1.valor_entero; ECHOYYPARSE(103, "<constante_logica> ::= false");}

constante_entera :  TOK_CONSTANTE_ENTERA    {
                                             $$.valor_entero = $1.valor_entero;
                                             ECHOYYPARSE(104, "<constante_entera> ::= numero");}

identificador   :   TOK_IDENTIFICADOR
                    {
                        informacion *inf = crear_informacion($1.identificador, categoria_actual,
                            tipo_actual, clase_actual, tamano_actual, 0, 0, 0, 0, 0);
                        if(inf == NULL) return error_unknown();
                        if(add_tabla_global(tsymb, $1.identificador, inf) == ERR)
                            return error_sem(dec_dup, $1.identificador);
                        declarar_variable(yyout, $1.identificador, tipo_actual, tamano_actual);
                        ECHOYYPARSE(108, "<identificador> ::= TOK_IDENTIFICADOR");
                    }

%%
int mismo_tipo(int tipo, int op1tipo, int op2tipo){
    return op1tipo == op2tipo && tipo==op1tipo;
}

void escribir_aux(informacion info){
  if(info.es_direccion == 1) escribir_operando(yyout, info.identificador, 1);
  else {
    char aux[16];
    snprintf(aux, 15, "%d", info.valor_entero);
    escribir_operando(yyout, aux, 0);
  }
}

void ejecutar_operacion(int op, informacion info1, informacion info2){
  if(op == SUMA)
    sumar(yyout, info1.es_direccion, info2.es_direccion);
  else if(op == RESTA)
    restar(yyout, info1.es_direccion, info2.es_direccion);
  else if(op == MULTIPLICACION)
    multiplicar(yyout, info1.es_direccion, info2.es_direccion);
  else if(op == DIVISION)
    dividir(yyout, info1.es_direccion, info2.es_direccion);
  else if(op == CAMBIO_SIGNO)
    cambiar_signo(yyout, info1.es_direccion);
  else if(op == AND)
    y(yyout, info1.es_direccion, info2.es_direccion);
  else if(op == OR)
    o(yyout, info1.es_direccion, info2.es_direccion);
  else if(op == IGUAL)
    igual(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual);
  else if(op == DISTINTO)
    distinto(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual);
  else if(op == MENORIGUAL)
    menor_igual(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual);
  else if(op == MAYORIGUAL)
    mayor_igual(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual);
  else if(op == MENOR)
    menor(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual);
  else if(op == MAYOR)
    mayor(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual);

}

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
    int local=FALSE;
    int insideFunc=FALSE;
    int salir = FALSE;
    int num_variables_locales_actual;
    int pos_variable_local_actual;
    int num_parametros_actual;
    int pos_parametro_actual;
    char nombreFuncionActual[200];
    int en_explit = 0;
    int num_parametros_llamada_actual = 0;
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

%type <atrib> elemento_vector exp comparacion constante constante_logica constante_entera if_cond if_then bucle_cond fn_name fn_declaration idf_llamada_funcion
%start programa

%%
programa        :  {tsymb = create_tabla_simbolos();}
    TOK_MAIN '{' {escribir_cabecera_bss(yyout); categoria_actual = VARIABLE; /*CAMBIAR CUANDO FUNCIONES*/}
    declaraciones  {escribir_subseccion_data(yyout); escribir_segmento_codigo(yyout);clase_actual=-1;tipo_actual=-1;}
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
                        tamano_actual = $4.valor_entero;
                    }

identificadores :   identificador
    {ECHOYYPARSE(18, "<identificadores> ::= <identificador>");}
                |   identificador ',' identificadores
    {ECHOYYPARSE(19, "<identificadores> ::= <identificador> , <identificadores>");}

funciones       :   funcion funciones   {ECHOYYPARSE(20, "<funciones> ::= <funcion> <funciones>");}
                |                       {ECHOYYPARSE(21, "<funciones> ::= ");}


funcion         :   fn_declaration sentencias '}'
    {
      cerrar_ambito_local(tsymb);
      local = FALSE;
      informacion *inf = buscar_identificador(tsymb, $1.identificador);
      if (inf == NULL) return error_sem(undec_acc, $1.identificador);
      inf->num_param = num_parametros_actual;
      inf->num_variables = num_variables_locales_actual;
      if(salir==FALSE) return error_sem(f_noret, $1.identificador);
      salir = FALSE;
      insideFunc = FALSE;
    }

fn_declaration  :   fn_name '(' parametros_funcion ')' '{' declaraciones_funcion
    {
      informacion *inf = buscar_identificador(tsymb, $1.identificador);
      if (inf == NULL) return error_sem(undec_acc, $1.identificador);
      inf->num_param = num_parametros_actual;
      inf->num_variables = num_variables_locales_actual;
      strcpy($$.identificador, $1.identificador);
      declararFuncion(yyout, $1.identificador, num_variables_locales_actual);
      insideFunc = TRUE;
    }

fn_name         :   TOK_FUNCTION tipo TOK_IDENTIFICADOR
    {
      if(local==TRUE) return error_sem(funcInsideFunc, $3.identificador);
      informacion *inf = crear_informacion($3.identificador, FUNCION,
          tipo_actual, clase_actual, tamano_actual, 0, 0, 0, 0, 0);
      if(inf == NULL) return error_unknown();
      if(iniciar_ambito_local(tsymb, $3.identificador, inf) == ERR)
          return error_sem(errAmbLoc, $3.identificador);
      num_variables_locales_actual = 0;
      pos_variable_local_actual = 1;
      num_parametros_actual = 0;
      pos_parametro_actual = 0;
      local = TRUE;
      strcpy($$.identificador, $3.identificador);
      strcpy(nombreFuncionActual, $3.identificador);
    }




parametros_funcion  :   parametro_funcion resto_parametros_funcion
    {ECHOYYPARSE(23, "<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
                    |
    {ECHOYYPARSE(24, "<parametros_funcion> ::= ");}

resto_parametros_funcion    :   ';' parametro_funcion resto_parametros_funcion
    {ECHOYYPARSE(25, "<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>");}
                            |
    {ECHOYYPARSE(26, "<resto_parametros_funcion> ::= ");}

parametro_funcion   :   tipo idpf
    {ECHOYYPARSE(27, "<parametro_funcion> ::= <tipo> <identificador>");}

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

asignacion      :   TOK_IDENTIFICADOR '=' exp {
                                                informacion *i;
                                                if(local==FALSE){
                                                  i = buscar_identificador(tsymb, $1.identificador);
                                                  if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                                  else if (i->categoria == FUNCION) return error_sem(func_as_var, $1.identificador);
                                                  else if (i->clase == VECTOR) return error_sem(noindex_v, $1.identificador);
                                                  else if (i->tipo != $3.tipo) return error_sem(incomp_assgn, NULL);
                                                  asignar(yyout, $1.identificador, $3.es_direccion);
                                                }
                                                else{
                                                  i = search_tabla_local(tsymb, $1.identificador);
                                                  if(i==NULL){
                                                    i = search_tabla_global(tsymb, $1.identificador);
                                                    if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                                    else if (i->categoria == FUNCION) return error_sem(func_as_var, $1.identificador);
                                                    else if (i->clase == VECTOR) return error_sem(noindex_v, $1.identificador);
                                                    else if (i->tipo != $3.tipo) return error_sem(incomp_assgn, NULL);
                                                    asignar(yyout, $1.identificador, $3.es_direccion);
                                                  }
                                                  else{
                                                    if (i->categoria == FUNCION) return error_sem(func_as_var, $1.identificador);
                                                    else if (i->clase == VECTOR) return error_sem(noindex_v, $1.identificador);
                                                    else if (i->tipo != $3.tipo) return error_sem(incomp_assgn, NULL);
                                                    if(i->categoria==PARAMETRO){
                                                      escribirParametro(yyout, i->pos_param, num_parametros_actual);
                                                    }
                                                    else if(i->categoria==VARIABLE){
                                                      escribirVariableLocal(yyout, i->pos_variable);
                                                    }
                                                    asignarDestinoEnPila(yyout, $3.es_direccion);
                                                  }
                                                }
                                                ECHOYYPARSE(43, "<asignacion> ::= <TOK_IDENTIFICADOR> = <exp>");}
                |   elemento_vector '=' exp {if ($1.tipo != $3.tipo) return error_sem(incomp_assgn, NULL);
                                            asignarElementoVector(yyout, $3.es_direccion);
                                            ECHOYYPARSE(44, "<asignacion> ::= <elemento_vector> = <exp>");}

elemento_vector :   TOK_IDENTIFICADOR '[' exp ']'{if($3.tipo != ENTERO) return error_sem(index_noint, NULL);
                                                  informacion *i = buscar_identificador(tsymb, $1.identificador);
                                                  if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                                  else if (i->categoria == FUNCION) return error_sem(func_as_var, $1.identificador);
                                                  else if (i->clase != VECTOR) return error_sem(index_in_nov, $1.identificador);
                                                  $$.tipo = i->tipo;
                                                  $$.es_direccion = 1;
                                                  escribir_elemento_vector(yyout, $1.identificador, i->tamano, $3.es_direccion);
                                                  ECHOYYPARSE(48, "<elemento_vector> ::= <TOK_IDENTIFICADOR> [ <exp> ]");}

condicional     :   if_cond ')' '{' sentencias '}'
                                  {
                                    ifthen_fin(yyout, $1.etiqueta);
                                    ECHOYYPARSE(50, "<condicional> ::= if ( <exp> ) { <sentencias> }");}
                |   if_then TOK_ELSE '{' sentencias '}' {
                                                        ifthenelse_fin(yyout, $1.etiqueta);
                                                        }
if_cond         :   TOK_IF '(' exp {
                                    if($3.tipo != BOOLEAN) error_sem(cond_int, NULL);
                                    $$.etiqueta = etiqueta_actual;
                                    etiqueta_actual++;
                                    ifthenelse_inicio(yyout, $3.es_direccion, $$.etiqueta);
                                    }
if_then         :   if_cond ')' '{' sentencias '}' {
                                                    $$.etiqueta = $1.etiqueta;
                                                    ifthenelse_fin_then(yyout, $$.etiqueta);
                                                    }
bucle           :   bucle_cond ')' '{' sentencias '}'
                                    {
                                      while_fin(yyout, $1.etiqueta);
                                      ECHOYYPARSE(52, "<bucle> ::= while ( <exp> ) { <sentencias> }");}
bucle_cond      :   TOK_WHILE {
                               $<atrib>$.etiqueta = etiqueta_actual;
                               etiqueta_actual++;
                               while_inicio(yyout, $<atrib>$.etiqueta);}[etiq]
                    '(' exp {
                              if($4.tipo != BOOLEAN) error_sem(bucl_cond_int, NULL);
                              while_exp_pila(yyout, $4.es_direccion, $<atrib>$.etiqueta);
                              $$.etiqueta = $<atrib>$.etiqueta;
                              }

lectura         :   TOK_SCANF TOK_IDENTIFICADOR {
                                                informacion *i;
                                                if(local==FALSE){
                                                  i = buscar_identificador(tsymb, $2.identificador);
                                                  if (i == NULL) return error_sem(undec_acc, $2.identificador);
                                                  else if (i->categoria == FUNCION) return error_sem(func_as_var, $2.identificador);
                                                  else if (i->clase == VECTOR) return error_sem(noindex_v, $2.identificador);
                                                  leer(yyout, i->identificador, i->tipo);
                                                }
                                                else{
                                                  i = search_tabla_local(tsymb, $2.identificador);
                                                  if(i==NULL){
                                                    i = search_tabla_global(tsymb, $2.identificador);
                                                    if (i == NULL) return error_sem(undec_acc, $2.identificador);
                                                    else if (i->categoria == FUNCION) return error_sem(func_as_var, $2.identificador);
                                                    else if (i->clase == VECTOR) return error_sem(noindex_v, $2.identificador);
                                                    leer(yyout, i->identificador, i->tipo);
                                                  }
                                                  else{
                                                    if (i->categoria == FUNCION) return error_sem(func_as_var, $2.identificador);
                                                    else if (i->clase == VECTOR) return error_sem(noindex_v, $2.identificador);
                                                    if(i->categoria==PARAMETRO){
                                                      escribirParametro(yyout, i->pos_param, num_parametros_actual);
                                                    }
                                                    else if(i->categoria==VARIABLE){
                                                      escribirVariableLocal(yyout, i->pos_variable);
                                                    }
                                                    leer_en_dir_pila(yyout, i->tipo);
                                                  }
                                                }
                                                ECHOYYPARSE(54, "<lectura> ::= scanf <TOK_IDENTIFICADOR>");}
escritura       :   TOK_PRINTF exp  {escribir(yyout, $2.es_direccion, $2.tipo);
                                    ECHOYYPARSE(56, "<escritura> ::= printf <exp>");}
retorno_funcion :   TOK_RETURN exp
                    {
                      if(insideFunc==FALSE) return error_sem(ret_nof, NULL);
                      informacion *i =buscar_identificador(tsymb, nombreFuncionActual);
                      if (i == NULL) return error_sem(undec_acc, nombreFuncionActual);
                      if(i->tipo!=$2.tipo) return error_sem(ret_wrongtype, NULL);
                      if($2.clase == VECTOR) return error_sem(return_nosc, NULL);
                      retornarFuncion(yyout, $2.es_direccion);
                      salir = TRUE;
                      ECHOYYPARSE(61, "<retorno_funcion> ::= return <exp>");}

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
                                              etiqueta_actual++; // TODO CHECK
                                            }
                                            ECHOYYPARSE(79, "<exp> ::= ! <exp>");}
                |   TOK_IDENTIFICADOR   {
                                        informacion *i;
                                        $$.es_direccion = 1;
                                        if(local==FALSE){
                                          i = buscar_identificador(tsymb, $1.identificador);
                                          if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                          else if (i->categoria == FUNCION) return error_sem(func_as_var, $1.identificador);
                                          else if (i->clase == VECTOR) return error_sem(noindex_v, $1.identificador);
                                          strcpy($$.identificador, $1.identificador);
                                          escribir_aux($$);
                                        }
                                        else{
                                          i = search_tabla_local(tsymb, $1.identificador);
                                          if(i==NULL){
                                            i = search_tabla_global(tsymb, $1.identificador);
                                            if (i == NULL) return error_sem(undec_acc, $1.identificador);
                                            else if (i->categoria == FUNCION) return error_sem(func_as_var, $1.identificador);
                                            else if (i->clase == VECTOR) return error_sem(noindex_v, $1.identificador);
                                            strcpy($$.identificador, $1.identificador);
                                            escribir_aux($$);
                                          }
                                          else{
                                            if (i->categoria == FUNCION) return error_sem(func_as_var, $1.identificador);
                                            else if (i->clase == VECTOR) return error_sem(noindex_v, $1.identificador);
                                            strcpy($$.identificador, $1.identificador);
                                            if(i->categoria==PARAMETRO){
                                              escribirParametro(yyout, i->pos_param, num_parametros_actual);
                                            }
                                            else if(i->categoria==VARIABLE){
                                              escribirVariableLocal(yyout, i->pos_variable);
                                            }
                                          }
                                        }
                                        $$.tipo = i->tipo;
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
                |   idf_llamada_funcion '(' lista_expresiones ')' {
                                        informacion *inf = buscar_identificador(tsymb, $1.identificador);
                                        if(inf == NULL) return error_sem(undec_acc, $1.identificador);
                                        if(inf->num_param!=num_parametros_llamada_actual) return error_sem(inc_num_pam, $1.identificador);
                                        en_explit = 0;
                                        $$.tipo = inf->tipo;
                                        $$.es_direccion = 0;
                                        llamarFuncion(yyout,$1.identificador,num_parametros_llamada_actual);
                                        ECHOYYPARSE(88, "<exp> ::= <idf_llamada_funcion> ( <lista_expresiones> )");}

idf_llamada_funcion     :   TOK_IDENTIFICADOR {
      informacion *i = buscar_identificador(tsymb, $1.identificador);
      if(i == NULL) return error_sem(undec_acc, $1.identificador);
      if(i->categoria!=FUNCION) return error_sem(funcIsNotFunc, $1.identificador);
      if(en_explit==1) return error_sem(callf_param, $1.identificador);
      en_explit = 1;
      num_parametros_llamada_actual=0;
	    strcpy($$.identificador, $1.identificador);
}

lista_expresiones       :   exp {operandoEnPilaAArgumento(yyout,$1.es_direccion);} resto_lista_expresiones
    { num_parametros_llamada_actual++;
      ECHOYYPARSE(89, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
                        |
    {ECHOYYPARSE(90, "<lista_expresiones> ::= ");}
resto_lista_expresiones :   ',' exp {operandoEnPilaAArgumento(yyout,$2.es_direccion);} resto_lista_expresiones
    { num_parametros_llamada_actual++;
      ECHOYYPARSE(91, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
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
idpf            :   TOK_IDENTIFICADOR
                    {
                        if(clase_actual==VECTOR) return error_sem(param_nosc, NULL);
                        informacion *inf = crear_informacion($1.identificador, PARAMETRO,
                            tipo_actual, clase_actual, tamano_actual, 0, 0, pos_parametro_actual, 0, 0);
                        if(inf == NULL) return error_unknown();
                        if(insertar_variable(tsymb, $1.identificador, inf) == ERR)
                            return error_sem(dec_dup, $1.identificador);
                        pos_parametro_actual++;
                        num_parametros_actual++;
                    }



identificador   :   TOK_IDENTIFICADOR
                    {
                        if(local==FALSE){
                          if((tamano_actual < 0 || tamano_actual>MAX_VECTOR) && clase_actual==VECTOR)
                              return error_sem(size_v, $1.identificador);
                          informacion *inf = crear_informacion($1.identificador, categoria_actual,
                              tipo_actual, clase_actual, tamano_actual, 1, 0, 0, 0, 0);
                          if(inf == NULL) return error_unknown();
                          if(add_tabla_global(tsymb, $1.identificador, inf) == ERR)
                              return error_sem(dec_dup, $1.identificador);
                          declarar_variable(yyout, $1.identificador, tipo_actual, tamano_actual);
                        }
                        else{
                          informacion *inf = crear_informacion($1.identificador, VARIABLE,
                              tipo_actual, clase_actual, tamano_actual, 0, 0, 0, 0, pos_variable_local_actual);
                          if(inf == NULL) return error_unknown();
                          if(clase_actual==VECTOR) return error_sem(local_nosc, $1.identificador);
                          if(add_tabla_local(tsymb, $1.identificador, inf) == ERR)
                              return error_sem(dec_dup, $1.identificador);
                          pos_variable_local_actual++;
                          num_variables_locales_actual++;
                        }
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
    igual(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual++);
  else if(op == DISTINTO)
    distinto(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual++);
  else if(op == MENORIGUAL)
    menor_igual(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual++);
  else if(op == MAYORIGUAL)
    mayor_igual(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual++);
  else if(op == MENOR)
    menor(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual++);
  else if(op == MAYOR)
    mayor(yyout, info1.es_direccion, info2.es_direccion, etiqueta_actual++);
}

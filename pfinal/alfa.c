#include <stdio.h>
#include "alfa.h"
#include "y.tab.h"


int yyerror(char *s){
    return fprintf(stderr, "****Error sintactico en [lin %d, col %d]\n", yylineno, column);
}

int error_sem(s_error error, char *identificador){
  if (error == dec_dup)
    fprintf(stderr,
      "****Error semantico en lin %d: Declaracion duplicada.\n",
        yylineno);
  else if (error == undec_acc)
    fprintf(stderr,
      "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n",
        yylineno, identificador);
  else if (error == arit_bool)
    fprintf(stderr,
      "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n",
        yylineno);
  else if (error == log_int)
    fprintf(stderr,
      "****Error semantico en lin %d: Operacion logica con operandos int.\n",
        yylineno);
  else if (error == comp_bool)
    fprintf(stderr,
      "****Error semantico en lin %d: Comparacion con operandos boolean.\n",
        yylineno);
  else if (error == cond_int)
    fprintf(stderr,
      "****Error semantico en lin %d: Condicional con condicion de tipo int.\n",
        yylineno);
  else if (error == bucl_cond_int)
    fprintf(stderr,
      "****Error semantico en lin %d: Bucle con condicion de tipo int.\n",
        yylineno);
  else if (error == inc_num_pam)
    fprintf(stderr,
      "****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion.\n",
        yylineno);
  else if (error == incomp_assgn)
    fprintf(stderr,
      "****Error semantico en lin %d: Asignacion incompatible.\n",
        yylineno);
  else if (error == size_v)
    fprintf(stderr,
      "****Error semantico en lin %d: El tamanyo del vector %s excede los limites permitidos (1,64).\n",
        yylineno, identificador);
  else if (error == index_in_nov)
    fprintf(stderr,
      "****Error semantico en lin %d: Intento de indexacion de una variable que no es de tipo vector.\n",
        yylineno);
  else if (error == index_noint)
    fprintf(stderr,
      "****Error semantico en lin %d: El indice en una operacion de indexacion tiene que ser de tipo entero.\n",
        yylineno);
  else if (error == f_noret)
    fprintf(stderr,
      "****Error semantico en lin %d: Funcion %s sin sentencia de retorno.\n",
        yylineno, identificador);
  else if (error == ret_nof)
    fprintf(stderr,
      "****Error semantico en lin %d: Sentencia de retorno fuera del cuerpo de una función.\n",
        yylineno);
  else if (error == callf_param)
    fprintf(stderr,
      "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones.\n",
        yylineno);
  else if (error == local_nosc)
    fprintf(stderr,
      "****Error semantico en lin %d: Variable local de tipo no escalar.\n",
        yylineno);
  return 1;
}

int error_unknown(){
  fprintf(stderr, "****Error interno del programa\n");
  return 1;
}

int main(int argc, char *argv[]){
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
    return yyparse();

}

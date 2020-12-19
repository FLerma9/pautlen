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
  else if (error == arit_bool)
    fprintf(stderr, 
      "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", 
        yylineno);
  else if (error == size_v)
    fprintf(stderr, 
      "****Error semantico en lin %d: El tamanyo del vector %s excede los limites permitidos (1,64).\n", 
        yylineno, identificador);
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
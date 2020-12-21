#include <stdio.h>
#include "alfa.h"
#include "y.tab.h"

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

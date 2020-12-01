#include "tablahash.h"
#include "tablasimbolos.h"
#include <stdio.h>

// FALTA FUNCION PARA ENCAPSULAR PROGRAMA DE PRUEBA

int main(int argc, char** argv){
    if(argc!=3){
      fprintf(stderr, "Numero de argumentos incorrecto, introducir ./alfa ficheroentrada.txt ficherosalida.txt\n");
      return ERR;
    }
    yyin = fopen(argv[1], "r");
    if(yyin==NULL){
      fprintf(stderr, "Error abriendo el fichero de entrada\n");
      return ERR;
    }
    yyout = fopen(argv[2], "w");
    if(yyout==NULL){
      fprintf(stderr, "Error abriendo el fichero de salida\n");
      return ERR;
    }
}

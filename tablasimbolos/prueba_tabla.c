#include "tablahash.h"
#include "tablasimbolos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// FALTA FUNCION PARA ENCAPSULAR PROGRAMA DE PRUEBA

int main(int argc, char** argv){
    char identificador[MAX_IDENTIFIER+1];
    char line[200];
    char *espacio;
    int valor;
    informacion *info = NULL;
    tabla_simbolos *tabla = NULL;
    FILE *f_in, *f_out;
    if(argc!=3){
      fprintf(stderr, "Numero de argumentos incorrecto, introducir ./prueba_tabla ficheroentrada.txt ficherosalida.txt\n");
      return ERR;
    }
    f_in = fopen(argv[1], "r");
    if(f_in==NULL){
      fprintf(stderr, "Error abriendo el fichero de entrada\n");
      return ERR;
    }
    f_out = fopen(argv[2], "w");
    if(f_out==NULL){
      fprintf(stderr, "Error abriendo el fichero de salida\n");
      return ERR;
    }

    tabla = create_tabla_simbolos();
    if(tabla == NULL){
        printf("%p\n",tabla);
        return ERR;
    }


    while(fgets(line, 200, f_in)){
        if((espacio = strchr(line, ' ')) == NULL){ // Busqueda
            espacio = strchr(line, '\n');
            espacio[0] = 0;
            strcpy(identificador, line);
            info = buscar_identificador(tabla, identificador);
            if(info == NULL) fprintf(f_out, "%s -1\n", identificador);
            else fprintf(f_out, "%s %d\n", identificador, info->tipo);
        }

        else{
            espacio[0] = 0; // Separamos identificador y valor
            strcpy(identificador, line);
            valor = atoi(espacio+1);

            if((strcmp("cierre", identificador) == 0) && valor == -999){
                cerrar_ambito_local(tabla);
                fprintf(f_out, "cierre\n");
            }
            else if(valor >= 0){
                info = crear_informacion(identificador, 0, valor, 0, 0, 0, 0, 0, 0);
                valor = insertar_variable(tabla, identificador, info);

                if(valor == OK)
                    fprintf(f_out, "%s\n", identificador);
                else
                    fprintf(f_out, "-1 %s\n", identificador);
            }
            else{
                info = crear_informacion(identificador, 0, valor, 0, 0, 0, 0, 0, 0);
                valor =iniciar_ambito_local(tabla, identificador, info);
                if(valor == OK)
                    fprintf(f_out, "%s\n", identificador);
                else
                    fprintf(f_out, "-1 %s\n", identificador);
            }
        }
    }
    fclose(f_in);
    fclose(f_out);
}

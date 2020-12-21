#include "tablahash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

tablahash * create_table(int tam){
    tablahash *tabla = NULL;
    tabla = malloc(sizeof(tabla));
    if(tabla == NULL){
        return NULL;
    }
    tabla->tam = tam;
    tabla->array = NULL;
    tabla->array = calloc(tam, sizeof(elemento));
    if(tabla->array == NULL){
        free(tabla);
        return NULL;
    }
    for (int i=0; i<tam; i++){
        tabla->array[i].value = NULL;
    }
    return tabla;
}

void destroy_table(tablahash *tabla){
    free(tabla->array);
    free(tabla);
}

void * search_table(tablahash *tabla, char *key){
    unsigned long itemhash = hash((unsigned char *)key);
    for(int i=0; i < tabla->tam; i++){
        unsigned long index = (itemhash+i)%tabla->tam;
        if(tabla->array[index].value == NULL) return NULL;
        if(strcmp(tabla->array[index].key, key) == 0) return tabla->array[index].value;
    }
    return NULL;
}

int insert_table(tablahash *tabla, char *key, void *value){
    unsigned long itemhash = hash((unsigned char *)key);
    for(int i=0; i < tabla->tam; i++){
        unsigned long index = (itemhash+i)%tabla->tam;
        if(tabla->array[index].value == NULL){
            tabla->array[index].value = value;
            strcpy(tabla->array[index].key, key);
            return OK;
        }
    }
    return ERR;
}

/* Utilizamos el hash djb2, de Dan Bernstein. Escogemos uno ya existente para
evitar hacer uno muy malo (con muchas colisiones) */

unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}
/*int main(){
    tablahash *tabla = create_table(100);
    insert_table(tabla, "HOLA", (void *)2);
    if((int) search_table(tabla, "HOLA") == 2)
    printf("HOLA BIEN");
    if(search_table(tabla, "AAAAAA") == NULL)
    printf("ERROR BIEN");
    destroy_table(tabla);
}
*/

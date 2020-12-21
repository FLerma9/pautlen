#include "tablahash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

tablahash * create_table(int tam){
    tablahash *tabla = NULL;
    tabla = malloc(sizeof(tablahash));
    if(tabla == NULL){
        return NULL;
    }
    tabla->tam = tam;
    tabla->array = NULL;
    tabla->array = calloc(tam, sizeof(elemento *));
    if(tabla->array == NULL){
        free(tabla);
        return NULL;
    }
    return tabla;
}

void destroy_table(tablahash *tabla){
    // MAYBE ADD FREE
    free(tabla->array);
    free(tabla);
}

void * search_table(tablahash *tabla, char *key){
    unsigned long itemhash = hash((unsigned char *)key);
    unsigned long index = (itemhash)%tabla->tam;
    if(tabla->array[index] == NULL) return NULL;
    else{
      elemento *actual = tabla->array[index];
      while(actual != NULL){
        if(strcmp(actual->key, key) == 0) return actual->value;
        actual = actual->siguiente;
      }
      return NULL;
    }
}

int insert_table(tablahash *tabla, char *key, void *value){
    unsigned long itemhash = hash((unsigned char *)key);
    unsigned long index = (itemhash)%tabla->tam;
    if(tabla->array[index] == NULL){
        elemento *elem = NULL;
        if (NULL == (elem = malloc(sizeof(elemento)))) return ERR;
        tabla->array[index] = elem;
        tabla->array[index]->value = value;
        tabla->array[index]->siguiente = NULL;
        strcpy(tabla->array[index]->key, key);
        return OK;
    } else{
      elemento *elem = NULL;
      if (NULL == (elem = malloc(sizeof(elemento)))) return ERR;
      elemento *aux;
      aux = tabla->array[index];
      tabla->array[index] = elem;
      tabla->array[index]->value = value;
      strcpy(tabla->array[index]->key, key);
      tabla->array[index]->siguiente = aux;
      return OK;
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
}*/

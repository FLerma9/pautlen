#include <stdlib.h>
#include <string.h>
#include "tablasimbolos.h"
#include "tablahash.h"
#include <stdio.h>

tabla_simbolos *create_tabla_simbolos(){
    tabla_simbolos *tabla = NULL;
    tabla = malloc(sizeof(tabla_simbolos));
    if(tabla == NULL) return NULL;

    tabla->global = NULL;
    tabla->local = NULL;
    if(iniciar_ambito_global(tabla) == ERR){
        free(tabla);
        return NULL;
    }

    return tabla;
}

void destroy_tabla_simbolos(tabla_simbolos *tabla){
    if(tabla->global != NULL) cerrar_ambito_global(tabla);
    if(tabla->local != NULL) cerrar_ambito_local(tabla);
    free(tabla);
}

int iniciar_ambito_global(tabla_simbolos *tabla){
    tabla->global = create_table(TAM_LOCAL);
    if(tabla->global == NULL) return ERR;
    return OK;
}

void cerrar_ambito_global(tabla_simbolos *tabla){
    if(tabla->global != NULL){
        for(int i=0; i<tabla->global->tam; i++){
            if(tabla->global->array[i].value != NULL)
                free(tabla->global->array[i].value);
        }
    }
}

int iniciar_ambito_local(tabla_simbolos *tabla, char *key, informacion *info){
    if (add_tabla_global(tabla, key, info) == ERR) return ERR;
    tabla->local = create_table(TAM_LOCAL);
    if(tabla->local == NULL) return ERR;
    if(add_tabla_local(tabla, key, info) == ERR) return ERR;
    return OK;
}

void cerrar_ambito_local(tabla_simbolos *tabla){
    if(tabla->local != NULL){
        for(int i=0; i<tabla->local->tam; i++){
            if(tabla->local->array[i].value != NULL)
                free(tabla->local->array[i].value);
        }
        free(tabla->local);
        tabla->local = NULL;
    }
}

int add_tabla_global(tabla_simbolos *tabla, char *key, informacion *info){
    void *r = search_table(tabla->global, key);
    if (r != NULL) return ERR;
    return insert_table(tabla->global, key, (void *)info);
}

informacion *search_tabla_global(tabla_simbolos *tabla, char *key){
    return (informacion *)search_table(tabla->global, key);

}

int add_tabla_local(tabla_simbolos *tabla, char *key, informacion *info){
    void *r = search_table(tabla->local, key);
    if (r != NULL) return ERR;
    return insert_table(tabla->local, key, (void *)info);
}

informacion *search_tabla_local(tabla_simbolos *tabla, char *key){
    return (informacion *)search_table(tabla->local, key);
}

informacion *crear_informacion(const char *identificador, int categoria,
    int tipo, int escalar_o_vector, int size, int num_param, int pos_param,
    int num_variables, int pos_variable){
        if(strlen(identificador) > MAX_IDENTIFIER) return NULL;
        informacion *info = NULL;
        info = malloc(sizeof(informacion));
        if(info == NULL) return NULL;

        strcpy(info->identificador, identificador);
        info->categoria = categoria;
        info->tipo = tipo;
        info->escalar_o_vector = escalar_o_vector;
        info->size = size;
        info->num_param = num_param;
        info->pos_param = pos_param;
        info->num_variables = num_variables;
        info->pos_variable = pos_variable;
        return info;
}

int insertar_variable(tabla_simbolos *tabla, char *key, informacion *info){
    if(tabla->local == NULL) return add_tabla_global(tabla,key,info);
    return add_tabla_local(tabla,key,info);
}

/*int insertar_funcion(tabla_simbolos *tabla, char *key, informacion *info){
    if(ERR == add_tabla_global(tabla,key,info)) return ERR;
    if(ERR == iniciar_ambito_local(tabla,key,info)) return ERR;
    return add_tabla_local(tabla,key,info);
}*/

informacion *buscar_identificador(tabla_simbolos *tabla, char *key){
    informacion *ret;
    if(tabla->local != NULL){
        ret = search_tabla_local(tabla,key);
        if(ret != NULL) return ret;
    }
    return search_tabla_global(tabla,key);
}

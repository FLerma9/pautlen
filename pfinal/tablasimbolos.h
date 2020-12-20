#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "tablahash.h"

#define TAM_GLOBAL 5000
#define TAM_LOCAL 500

typedef struct informacion{
    char identificador[MAX_IDENTIFIER+1];
    int categoria;
    int tipo;
    int clase;
    int tamano;
    int valor_entero;
    int es_direccion;
    int num_param;
    int pos_param;
    int num_variables;
    int pos_variable;
} informacion;

typedef struct tabla_simbolos{
    tablahash *global;
    tablahash *local;
}tabla_simbolos;

tabla_simbolos *create_tabla_simbolos();
void destroy_tabla_simbolos(tabla_simbolos *tabla);

int iniciar_ambito_global(tabla_simbolos *tabla);
void cerrar_ambito_global(tabla_simbolos *tabla);

int iniciar_ambito_local(tabla_simbolos *tabla, char *key, informacion *info);
void cerrar_ambito_local(tabla_simbolos *tabla);

int add_tabla_global(tabla_simbolos *tabla, char *key, informacion *info);
informacion *search_tabla_global(tabla_simbolos *tabla, char *key);

int add_tabla_local(tabla_simbolos *tabla, char *key, informacion *info);
informacion *search_tabla_local(tabla_simbolos *tabla, char *key);


/* Crea una variable de informacion con los valores pasados */
informacion *crear_informacion(const char *identificador, int categoria,
    int tipo, int clase, int tamano, int valor_entero, int num_param, int pos_param,
    int num_variables, int pos_variable);


/* Inserta una variable en la tabla */
int insertar_variable(tabla_simbolos *tabla, char *key, informacion *info);
//int insertar_funcion(tabla_simbolos *tabla, char *key, informacion *info);


/* Busca un identificador en la tabla */
informacion *buscar_identificador(tabla_simbolos *tabla, char *key);

#endif

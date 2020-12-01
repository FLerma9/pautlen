#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "tablahash.h"

#define TAM_GLOBAL 5000
#define TAM_LOCAL 500

#define MAX_VECTOR 64

#define VARIABLE 1
#define PARAMETRO 2
#define FUNCION 3

#define BOOLEAN 1
#define INT 2

#define ESCALAR 1
#define VECTOR 2

typedef struct informacion{
    char identificador[MAX_IDENTIFIER+1];
    int categoria;
    int tipo;
    int escalar_o_vector;
    int size;
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

informacion *crear_informacion(const char *identificador, int categoria,
    int tipo, int escalar_o_vector, int size, int num_param, int pos_param,
    int num_variables, int pos_variable);


#endif

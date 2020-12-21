#ifndef TABLAHASH_H
#define TABLAHASH_H

#define MAX_IDENTIFIER 100

#define OK 0
#define ERR 1

typedef struct elemento elemento;
struct elemento{
    void *value;
    char key[MAX_IDENTIFIER+1];
    elemento *siguiente;
};

typedef struct tablahash{
    elemento **array;
    int tam;
}tablahash;

tablahash * create_table(int tam);
void destroy_table(tablahash *tabla);
void * search_table(tablahash *tabla, char *key);
int insert_table(tablahash *tabla, char *key, void *value);
unsigned long hash(unsigned char *str);

#endif

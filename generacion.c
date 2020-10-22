#include "generacion.h"

void escribir_cabecera_bss(FILE* fpasm){
    if(fpasm == NULL) return;
    fprintf(fpasm, "segment .bss\n");
    fprintf(fpasm, "\t__esp resd 1\n");
}

void escribir_subseccion_data(FILE* fpasm){
    char msg_div_0[] = "ERROR: division por 0";
    char msg_index_out_of_range[] = "ERROR: indice fuera de rango";
    if(fpasm == NULL) return;
    fprintf(fpasm, "segment .data\n");
    fprintf(fpasm, "\t_msgErrorDiv0 db \"%s\", 0\n", msg_div_0);
    fprintf(fpasm, "\t_msgIndexOutOfRange db \"%s\", 0\n", msg_index_out_of_range);
}

void declarar_variable(FILE* fpasm, char * nombre, int tipo, int tamano){
    if(fpasm == NULL) return;
    if(tipo==ENTERO || tipo==BOOLEANO)
        fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
}

void escribir_segmento_codigo(FILE* fpasm){
    if(fpasm == NULL) return;
    fprintf(fpasm, "segment .txt\n");
    fprintf(fpasm, "global main\n");
    // cosas
}

void aux_pop_op(FILE* fpasm, int es_variable, int numOp){
    if(fpasm == NULL || numOp < 1 || numOp > 2) return;
    char registro[2][4] = {"eax, edx"};
    fprintf(fpasm, "pop dword %s\n", registro[numOp-1]); // operando 2
    if(es_variable) fprintf(fpasm, "mov dword %s, [%s]\n", registro[numOp-1], registro[numOp-1]);    
}

void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "add eax, edx\n"); // add operando 1 operando 2
    fprintf(fpasm, "push dword eax\n"); // push a pila
}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "sub eax, edx\n"); // sub operando 1 operando 2
    fprintf(fpasm, "push dword eax\n"); // push a pila
}

void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "imul edx\n"); // mult operando 1 operando 2 -> edx:eax
    fprintf(fpasm, "push dword edx\n"); // push a pila edx
    fprintf(fpasm, "push dword edx\n"); // push a pila eax
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "div edx\n"); // div operando 1 operando 2 -> edx:eax
    fprintf(fpasm, "push dword edx\n"); // push a pila edx
    fprintf(fpasm, "push dword edx\n"); // push a pila eax
    // CONTROLAR DIV0
}

void o(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "or eax, edx\n"); // or operando 1 operando 2
    fprintf(fpasm, "push dword eax\n"); // push a pila
}

void y(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "and eax, edx\n"); // y operando 1 operando 2
    fprintf(fpasm, "push dword eax\n"); // push a pila
}

void cambiar_signo(FILE* fpasm, int es_variable){}
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable, 1);
    fprintf(fpasm, "neg eax\n"); // neg operando
    fprintf(fpasm, "push dword eax\n"); // push a pila
}

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
    fprintf(fpasm, "pop eax\n");
    if(exp_es_variable == 1)
        fprintf(fpasm, "mov eax,[eax]\n");   
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_then_%d\n",etiqueta); 
}
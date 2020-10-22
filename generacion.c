#include "generacion.h"

#define NUMERR 2
#define NUMEXTF 7
char err[NUMERR][3][40] = {{"ErrorDiv0", "_msgErrorDiv0", "ERROR: division por 0"}, 
                {"ErrorIndexOutOfRange", "_msgErrorIndexOutOfRange", "ERROR: indice fuera de rango"}};
char func_extern[NUMEXTF][20] = {"print_int", "print_boolean", "print_string",
                             "print_blank", "print_endofline", "scan_int", "scan_boolean"};
                
void escribir_cabecera_bss(FILE* fpasm){
    if(fpasm == NULL) return;
    fprintf(fpasm, "segment .bss\n");
    fprintf(fpasm, "\t__esp resd 1\n");
}

void escribir_subseccion_data(FILE* fpasm){    
    if(fpasm == NULL) return;
    fprintf(fpasm, "segment .data\n");
    for(int i=0; i<NUMERR; i++)
        fprintf(fpasm, "\t%s db \"%s\", 0\n", err[i][1], err[i][2]); 
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
    fprintf(fpasm, "extern");
    for(int i=0; i<NUMEXTF; i++) fprintf(fpasm, " %s", func_extern[i]);
    fprintf(fpasm, "\n");
}

void escribir_inicio_main(FILE* fpasm){
    if(fpasm == NULL) return;
    fprintf(fpasm, "main:\n");
    fprintf(fpasm, "mov __esp, esp\n");
}

void escribir_fin(FILE* fpasm){
    if(fpasm == NULL) return;
    for(int i=0; i<NUMERR; i++){        
        fprintf(fpasm, "%s:\n", err[i][0]); // Erroretiqueta:
        fprintf(fpasm, "push dword %s:\n", err[i][1]); // push _msgError:
        fprintf(fpasm, "call print_string\n");
        fprintf(fpasm, "add esp, 4\n");
        fprintf(fpasm, "jmp near fin\n");
    }
    fprintf(fpasm, "fin:\n");
    fprintf(fpasm, "mov esp, __esp\n");
    fprintf(fpasm, "ret\n");
}
/*
    es_variable: 1 si es variable, 0 si no
    numReg: registro al que hacer pop.
        1 -> eax
        2 -> edx
        3 -> ecx
*/
void aux_pop_op(FILE* fpasm, int es_variable, int numReg){
    if(fpasm == NULL || numReg < 1 || numReg > 3) return;
    char registro[3][4] = {"eax", "edx", "ecx"};
    fprintf(fpasm, "pop dword %s\n", registro[numReg-1]); // operando 2
    if(es_variable) fprintf(fpasm, "mov dword %s, [%s]\n", registro[numReg-1], registro[numReg-1]);    
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
    fprintf(fpasm, "push dword eax\n"); // push a pila edx
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 3);
    // comprobar ecx != 0
    fprintf(fpasm, "cmp ecx, 0\n");
    fprintf(fpasm, "je ErrorDiv0\n");    
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "cdq\n");
    fprintf(fpasm, "idiv ecx\n"); // div operando 1 operando 2 -> edx:eax
    fprintf(fpasm, "push dword edx\n"); // push a pila edx resto
    fprintf(fpasm, "push dword eax\n"); // push a pila eax cociente
    
    
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

void cambiar_signo(FILE* fpasm, int es_variable){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable, 1);
    fprintf(fpasm, "neg eax\n"); // neg operando
    fprintf(fpasm, "push dword eax\n"); // push a pila
}

void no(FILE* fpasm, int es_variable, int cuantos_no){
    if(fpasm == NULL) return;    
    ifthenelse_inicio(fpasm, es_variable, cuantos_no);
    fprintf(fpasm, "push dword 0\n");
    ifthenelse_fin_then(fpasm, cuantos_no);
    fprintf(fpasm, "push dword 1\n");
    ifthenelse_fin(fpasm, cuantos_no);
}

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
    fprintf(fpasm, "pop eax\n");
    if(exp_es_variable == 1)
        fprintf(fpasm, "mov eax,[eax]\n");   
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_then_%d\n",etiqueta); 
}
#include "generacion.h"

#define NUMERR 2
#define NUMEXTF 7
char err[NUMERR][3][40] = {{"ErrorDiv0", "_msgErrorDiv0", "ERROR: division por 0"},
                {"ErrorIndexOutOfRange", "_msgErrorIndexOutOfRange", "ERROR: indice fuera de rango"}};
char func_extern[NUMEXTF][20] = {"print_int", "print_boolean", "print_string",
                             "print_blank", "print_endofline", "scan_int", "scan_boolean"};

/* TODO nos faltan los tabuladores, hay que mirar donde faltan, hacer
    con find and replace facil */

void aux_pop_op(FILE* fpasm, int es_variable, int numReg);

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
        fprintf(fpasm, "push dword %s\n", err[i][1]); // push _msgError: TODO
        fprintf(fpasm, "call print_string\n");
        fprintf(fpasm, "add esp, 4\n");
        fprintf(fpasm, "jmp near fin\n");
    }
    fprintf(fpasm, "fin:\n");
    fprintf(fpasm, "mov esp, __esp\n");
    fprintf(fpasm, "ret\n");
}


/*TODO: Duda*/
void escribir_operando(FILE* fpasm, char* nombre, int es_variable){
    if(fpasm == NULL) return;
    if(es_variable){
        fprintf(fpasm, "push dword _%s\n", nombre);
    }
    else{
        fprintf(fpasm, "push dword %s\n", nombre);
    }
}

void asignar(FILE* fpasm, char* nombre, int es_variable){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable, 1);
    fprintf(fpasm, "mov dword [_%s], eax\n", nombre );
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
    fprintf(fpasm, "je near ErrorDiv0\n");
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

void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, exp_es_variable, 1);
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_then_%d\n", etiqueta);
}

/*TODO usar aux_pop_op*/

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, exp_es_variable, 1);
    /*fprintf(fpasm, "pop eax\n");
    if(exp_es_variable == 1)
        fprintf(fpasm, "mov eax,[eax]\n");*/
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_then_%d\n", etiqueta);
}

void ifthen_fin(FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

void ifthenelse_fin_then( FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "jmp near fin_ifelse_%d\n", etiqueta);
    fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

void ifthenelse_fin( FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "fin_ifelse_%d:\n", etiqueta);
}

void while_inicio(FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "inicio_while_%d:\n", etiqueta);
}

void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, exp_es_variable, 1);
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_while_%d\n",etiqueta);
}

void while_fin( FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "jmp near inicio_while_%d\n", etiqueta);
    fprintf(fpasm, "fin_while_%d:\n", etiqueta);
}

void escribir_elemento_vector(FILE * fpasm,char * nombre_vector, int tam_max, int exp_es_direccion){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, exp_es_direccion, 1);
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "jl near ErrorIndexOutOfRange\n");
    fprintf(fpasm, "cmp eax, %d\n", tam_max-1);
    fprintf(fpasm, "jg near ErrorIndexOutOfRange\n");
    fprintf(fpasm, "mov dword edx, _%s\n", nombre_vector);
    fprintf(fpasm, "lea eax, [edx + eax*4]\n");
    fprintf(fpasm, "push dword eax\n");
}

void declararFuncion(FILE * fd_asm, char * nombre_funcion, int num_var_loc){
    if(fpasm == NULL) return;
    fprintf(fd_asm, "_%s:\n", nombre_funcion);
    fprintf(fd_asm, "push ebp\n");
    fprintf(fd_asm, "mov ebp, esp\n");
    fprintf(fd_asm, "sub esp, 4*%d\n", num_var_loc);
}

void retornarFuncion(FILE * fd_asm, int es_variable){
    aux_pop_op(fd_asm, es_variable, 1);
    fprintf(fd_asm, "\tmov esp,ebp\n"); /* restaurar el puntero de pila */
    fprintf(fd_asm, "\tpop ebp\n"); /* sacar de la pila ebp */
    fprintf(fd_asm, "\tret\n"); /* vuelve al programa llamante y saca de la pila la dir de retorno */
}

void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros){
    int d_ebp = 4*(1 + num_total_parametros - pos_parametro);
    fprintf(fpasm, "lea eax, [ebp + %d]\n", d_ebp);
    fprintf(fpasm, "push dword eax\n");
}

void escribirVariableLocal(FILE* fpasm, int posicion_variable_local){
    int d_ebp = 4*posicion_variable_local;
    fprintf(fpasm, "lea eax, [ebp - %d]\n", d_ebp);
    fprintf(fpasm, "push dword eax\n");
}

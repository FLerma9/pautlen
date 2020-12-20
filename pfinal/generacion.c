#include "generacion.h"

#define NUMERR 2
#define NUMEXTF 7

//Array con los posibles errores, primero es el nombre, segundo la etiqueta, tercero el mensaje
char err[NUMERR][3][50] = {{"ErrorDiv0", "_msgErrorDiv0", "****Error de ejecucion: Division por cero."},
                {"ErrorIndexOutOfRange", "_msgErrorIndexOutOfRange", "****Error de ejecucion: Indice fuera de rango."}};
//Array con las posibles funciones de la libreria alfalib
char func_extern[NUMEXTF][20] = {"print_int", "print_boolean", "print_string",
                             "print_blank", "print_endofline", "scan_int", "scan_boolean"};

/*  Funcion auxiliar que comprueba si es una variable el valor de la cima de la pila.
    Si es una variable le asignamos el valor al registro eax, si es un valor
    se le asigna directamente
    es_variable: 1 si es variable, 0 si no
    numReg: registro al que hacer pop.
        1 -> eax
        2 -> edx
        3 -> ecx
    */
void aux_pop_op(FILE* fpasm, int es_variable, int numReg){
    if(fpasm == NULL || numReg < 1 || numReg > 3) return;
    char registro[3][4] = {"eax", "edx", "ecx"};
    fprintf(fpasm, "\tpop dword %s\n", registro[numReg-1]); // Sacamos la cima de la pila
    // Si es una direccion, le asignamos el valor de esa direccion.
    if(es_variable) fprintf(fpasm, "\tmov dword %s, [%s]\n", registro[numReg-1], registro[numReg-1]);
}

void escribir_cabecera_bss(FILE* fpasm){
    if(fpasm == NULL) return;
    fprintf(fpasm, "\nsegment .bss\n");
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
    fprintf(fpasm, "\nsegment .txt\n");
    fprintf(fpasm, "global main\n");
    fprintf(fpasm, "extern");
    for(int i=0; i<NUMEXTF-1; i++) fprintf(fpasm, " %s,", func_extern[i]);
    fprintf(fpasm, " %s", func_extern[NUMEXTF-1]);
    fprintf(fpasm, "\n");
}

void escribir_inicio_main(FILE* fpasm){
    if(fpasm == NULL) return;
    fprintf(fpasm, "main:\n");
    fprintf(fpasm, "\tmov [__esp], esp\n");
}

void escribir_fin(FILE* fpasm){
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tjmp near fin\n");
    for(int i=0; i<NUMERR; i++){
        fprintf(fpasm, "\t%s:\n", err[i][0]); // Erroretiqueta:
        fprintf(fpasm, "\tpush dword %s\n", err[i][1]); // push _msgError: TODO
        fprintf(fpasm, "\tcall print_string\n");
        fprintf(fpasm, "\tadd esp, 4\n");
        fprintf(fpasm, "\tcall print_endofline\n");
        fprintf(fpasm, "\tjmp near fin\n");
    }
    fprintf(fpasm, "fin:\n");
    fprintf(fpasm, "\tmov esp, [__esp]\n");
    fprintf(fpasm, "\tret\n");
}

void escribir_operando(FILE* fpasm, char* nombre, int es_variable){
    if(fpasm == NULL) return;
    if(es_variable){
        fprintf(fpasm, "\tpush dword _%s\n", nombre);
    }
    else{
        fprintf(fpasm, "\tpush dword %s\n", nombre);
    }
}

void asignar(FILE* fpasm, char* nombre, int es_variable){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable, 1);
    fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre );
}

void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "\tadd eax, edx\n"); // add operando 1 operando 2
    fprintf(fpasm, "\tpush dword eax\n"); // push a pila
}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "\tsub eax, edx\n"); // sub operando 1 operando 2
    fprintf(fpasm, "\tpush dword eax\n"); // push a pila
}

void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "\timul edx\n"); // mult operando 1 operando 2 -> edx:eax
    fprintf(fpasm, "\tpush dword eax\n"); // push a pila edx
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 3);
    // comprobar ecx != 0
    fprintf(fpasm, "\tcmp ecx, 0\n");
    fprintf(fpasm, "\tje near ErrorDiv0\n");
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "\tcdq\n");
    fprintf(fpasm, "\tidiv ecx\n"); // div operando 1 operando 2 -> edx:eax
    //fprintf(fpasm, "\tpush dword edx\n"); // push a pila edx resto
    fprintf(fpasm, "\tpush dword eax\n"); // push a pila eax cociente


}

void o(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "\tor eax, edx\n"); // or operando 1 operando 2
    fprintf(fpasm, "\tpush dword eax\n"); // push a pila
}

void y(FILE* fpasm, int es_variable_1, int es_variable_2){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable_2, 2);
    aux_pop_op(fpasm, es_variable_1, 1);
    fprintf(fpasm, "\tand eax, edx\n"); // y operando 1 operando 2
    fprintf(fpasm, "\tpush dword eax\n"); // push a pila
}

void cambiar_signo(FILE* fpasm, int es_variable){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable, 1);
    fprintf(fpasm, "\tneg eax\n"); // neg operando
    fprintf(fpasm, "\tpush dword eax\n"); // push a pila
}

void no(FILE* fpasm, int es_variable, int cuantos_no){
    if(fpasm == NULL) return;
    ifthenelse_inicio(fpasm, es_variable, cuantos_no);
    fprintf(fpasm, "\tpush dword 0\n");
    ifthenelse_fin_then(fpasm, cuantos_no);
    fprintf(fpasm, "\tpush dword 1\n");
    ifthenelse_fin(fpasm, cuantos_no);
}

void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable2, 2);
    aux_pop_op(fpasm, es_variable1, 1);
    fprintf(fpasm, "\tcmp eax, edx\n"); // Comparamos los registros
    fprintf(fpasm, "\tje near igual%d\n", etiqueta); // Pusheamos 1 si es igual
    fprintf(fpasm, "\tpush dword 0\n"); // Pusheamos 0 si no es igual
    fprintf(fpasm, "\tjmp near fin_igual%d\n", etiqueta);
    fprintf(fpasm, "igual%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "fin_igual%d:\n", etiqueta); // Fin
}

void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable2, 2);
    aux_pop_op(fpasm, es_variable1, 1);
    fprintf(fpasm, "\tcmp eax, edx\n"); // Comparamos los registros
    fprintf(fpasm, "\tjne near distinto%d\n", etiqueta); // Pusheamos 1 si es distinto
    fprintf(fpasm, "\tpush dword 0\n"); //Pusheamos 0 si es igual
    fprintf(fpasm, "\tjmp near fin_distinto%d\n", etiqueta);
    fprintf(fpasm, "distinto%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "fin_distinto%d:\n", etiqueta); // Fin
}

void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable2, 2);
    aux_pop_op(fpasm, es_variable1, 1);
    fprintf(fpasm, "\tcmp eax, edx\n"); // Comparamos los registros
    fprintf(fpasm, "\tjle near menorigual%d\n", etiqueta); // Si es menor o igual pusheamos 1
    fprintf(fpasm, "\tpush dword 0\n"); // Si no pusheamos 0
    fprintf(fpasm, "\tjmp near fin_menorigual%d\n", etiqueta);
    fprintf(fpasm, "menorigual%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "fin_menorigual%d:\n", etiqueta); // Fin
}

void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable2, 2);
    aux_pop_op(fpasm, es_variable1, 1);
    fprintf(fpasm, "\tcmp eax, edx\n"); // Comparamos los registros
    fprintf(fpasm, "\tjge near mayorigual%d\n", etiqueta); // Si es mayor o igual pusheamos 1
    fprintf(fpasm, "\tpush dword 0\n"); // Si no pusheamos 0
    fprintf(fpasm, "\tjmp near fin_mayorigual%d\n", etiqueta);
    fprintf(fpasm, "mayorigual%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "fin_mayorigual%d:\n", etiqueta); // Fin
}

void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable2, 2);
    aux_pop_op(fpasm, es_variable1, 1);
    fprintf(fpasm, "\tcmp eax, edx\n"); // Comparamos los registros
    fprintf(fpasm, "\tjl near menor%d\n", etiqueta); // Si es menor pusheamos 1
    fprintf(fpasm, "\tpush dword 0\n"); // Si no pusheamos 0
    fprintf(fpasm, "\tjmp near fin_menor%d\n", etiqueta);
    fprintf(fpasm, "menor%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "fin_menor%d:\n", etiqueta); // Fin
}

void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable2, 2);
    aux_pop_op(fpasm, es_variable1, 1);
    fprintf(fpasm, "\tcmp eax, edx\n"); // Comparamos los registros
    fprintf(fpasm, "\tjg near mayor%d\n", etiqueta); // Si es mayor pusheamos 1
    fprintf(fpasm, "\tpush dword 0\n"); // Si no pusheamos 0
    fprintf(fpasm, "\tjmp near fin_mayor%d\n", etiqueta);
    fprintf(fpasm, "mayor%d:\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "fin_mayor%d:\n", etiqueta); // Fin
}

void leer(FILE* fpasm, char* nombre, int tipo){
    if(fpasm == NULL) return;
    escribir_operando(fpasm, nombre, 1); //Pusheamos como direccion con el nombre
    //Comprobamos antes si es un boolean o int para llamar a la funcion adecuada
    if(tipo == BOOLEANO) fprintf(fpasm, "\tcall scan_boolean\n");
    if(tipo == ENTERO) fprintf(fpasm, "\tcall scan_int\n");
    fprintf(fpasm, "\tadd esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo){
    if(fpasm == NULL) return;
    // Necesitamos el valor en la pila para imprimirlo, no la direccion
    if(es_variable){
      fprintf(fpasm, "\tpop dword eax\n");
      fprintf(fpasm, "\tmov dword eax, [eax]\n");
      fprintf(fpasm, "\tpush dword eax\n");
    }
    //Comprobamos antes si es un boolean o int para llamar a la funcion adecuada
    if(tipo == BOOLEANO) fprintf(fpasm, "\tcall print_boolean\n");
    if(tipo == ENTERO) fprintf(fpasm, "\tcall print_int\n");
    fprintf(fpasm, "\tadd esp, 4\n");
    fprintf(fpasm, "\tcall print_endofline\n");
}


void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, exp_es_variable, 1);
    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tje near fin_then_%d\n", etiqueta);
}


void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, exp_es_variable, 1);
    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tje near fin_then_%d\n", etiqueta);
}

void ifthen_fin(FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

void ifthenelse_fin_then( FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tjmp near fin_ifelse_%d\n", etiqueta);
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
    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tje near fin_while_%d\n",etiqueta);
}

void while_fin( FILE * fpasm, int etiqueta){
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tjmp near inicio_while_%d\n", etiqueta);
    fprintf(fpasm, "fin_while_%d:\n", etiqueta);
}

void escribir_elemento_vector(FILE * fpasm,char * nombre_vector, int tam_max, int exp_es_direccion){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, exp_es_direccion, 1);
    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tjl near ErrorIndexOutOfRange\n");
    fprintf(fpasm, "\tcmp eax, %d\n", tam_max-1);
    fprintf(fpasm, "\tjg near ErrorIndexOutOfRange\n");
    fprintf(fpasm, "\tmov dword edx, _%s\n", nombre_vector);
    fprintf(fpasm, "\tlea eax, [edx + eax*4]\n");
    fprintf(fpasm, "\tpush dword eax\n");
}

void declararFuncion(FILE * fd_asm, char * nombre_funcion, int num_var_loc){
    if(fd_asm == NULL) return;
    fprintf(fd_asm, "_%s:\n", nombre_funcion);
    fprintf(fd_asm, "\tpush ebp\n");
    fprintf(fd_asm, "\tmov ebp, esp\n");
    fprintf(fd_asm, "\tsub esp, 4*%d\n", num_var_loc);
}

void retornarFuncion(FILE * fd_asm, int es_variable){
    if(fd_asm == NULL) return;
    aux_pop_op(fd_asm, es_variable, 1);
    fprintf(fd_asm, "\tmov esp,ebp\n"); /* restaurar el puntero de pila */
    fprintf(fd_asm, "\tpop ebp\n"); /* sacar de la pila ebp */
    fprintf(fd_asm, "\tret\n"); /* vuelve al programa llamante y saca de la pila la dir de retorno */
}

void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros){
    int d_ebp = 4*(1 + num_total_parametros - pos_parametro);
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tlea eax, [ebp + %d]\n", d_ebp);
    fprintf(fpasm, "\tpush dword eax\n");
}

void escribirVariableLocal(FILE* fpasm, int posicion_variable_local){
    int d_ebp = 4*posicion_variable_local;
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tlea eax, [ebp - %d]\n", d_ebp);
    fprintf(fpasm, "\tpush dword eax\n");
}

void asignarDestinoEnPila(FILE* fpasm, int es_variable){
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tpop dword ebx\n");
    aux_pop_op(fpasm, es_variable, 1);
    fprintf(fpasm, "\tmov dword [ebx], eax\n");
}

void asignarElementoVector(FILE* fpasm, int es_variable){
    if(fpasm == NULL) return;
    aux_pop_op(fpasm, es_variable, 1);
    fprintf(fpasm, "\tpop dword ebx\n");
    fprintf(fpasm, "\tmov dword [ebx], eax\n");
}

void operandoEnPilaAArgumento(FILE * fpasm, int es_variable){
    if(fpasm == NULL) return;
    if(es_variable){
      fprintf(fpasm, "\tpop eax\n");
      fprintf(fpasm, "\tmov eax, [eax]\n");
      fprintf(fpasm, "\tpush eax\n");
    }
}

void limpiarPila(FILE * fpasm, int num_argumentos){
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tadd esp, %d\n", num_argumentos*4);
}

void llamarFuncion(FILE * fpasm, char * nombre_funcion, int num_argumentos){
    if(fpasm == NULL) return;
    fprintf(fpasm, "\tcall _%s\n", nombre_funcion);
    limpiarPila(fpasm, num_argumentos);
    fprintf(fpasm, "\tpush dword eax\n");
}

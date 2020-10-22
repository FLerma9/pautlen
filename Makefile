CC = gcc 
CFLAGS = -Wall -g 
GENFILE = generacion
EJEMPLOS = ej1

all: $(EJEMPLOS)

$(EJEMPLOS): %: %.c $(GENFILE).c $(GENFILE).h
	$(CC) $(CFLAGS) -c $@_asm generacion.c $@.c
	./$@_asm $@.asm
	nasm -g -o $@.o -f elf32 $@.asm
	$(CC) $(CFLAGS) -m32 -o $@ $@.o alfalib.o

.PHONY: clean

clean:
	rm -f $(EJEMPLOS) $(EJEMPLOS)_asm $(EJEMPLOS).asm $(EJEMPLOS).o 

	gcc -Wall -g -c ej1_asm generacion.c ej1.c
	./ej1_asm ej1.asm
	nasm -g -o ej1.o -f elf32 ej1.asm
	gcc -Wall -g -m32 -o ej1 ej1.o alfalib.o
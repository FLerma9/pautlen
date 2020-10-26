CC = gcc
CFLAGS = -Wall -g
GENFILE = generacion
EJEMPLOS = ej1 ej2 ej3 ej4 ej5 ej6 ej7
all: $(EJEMPLOS)

$(EJEMPLOS): %: %.c $(GENFILE).c $(GENFILE).h
	$(CC) $(CFLAGS) -o $@_asm generacion.c $@.c
	./$@_asm $@.asm
	nasm -g -o $@.o -f elf32 $@.asm
	$(CC) $(CFLAGS) -m32 -o $@ $@.o alfalib.o

#	EQUIVALENTE A \
	gcc -Wall -g -c ej1_asm generacion.c ej1.c \
	./ej1_asm ej1.asm \
	nasm -g -o ej1.o -f elf32 ej1.asm \
	gcc -Wall -g -m32 -o ej1 ej1.o alfalib.o \

.PHONY: clean

clean:
	rm -f $(foreach ej,$(EJEMPLOS),$(ej) $(ej)_asm $(ej).asm $(ej).o) 

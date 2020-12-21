.PHONY: clean all

MAIN=alfa
FLEX=flex
BISON=bison $(BFLAGS)
BFLAGS=-d -y -v
NASM=nasm -g -o
NASMFLAGS=-f elf32
CC = gcc
CFLAGS = -Wall -g

all: $(MAIN)

lex: $(MAIN).h y.tab.h alfa.l
	$(FLEX) alfa.l

bison: $(MAIN).h alfa.y
	$(BISON) alfa.y

$(MAIN): bison lex
	$(CC) $(CFLAGS) -o $@ lex.yy.c y.tab.c generacion.c tablahash.c tablasimbolos.c $@.c

clean: 
	rm -f lex.yy.c y.* $(MAIN)

.PHONY: clean all

MAIN=alfa
FLEX=flex
BISON=bison $(BFLAGS)
BFLAGS=-d -y -v
NASM=nasm -g -o
NASMFLAGS=-f elf32
CC = gcc
CFLAGS = -Wall -g
EJEMPLOS=ejemplo1 ejemplo2 ejemplo3
DIREJEMPLOS=ejemplos
DIRTESTS=tests
TESTS_ARIT:=$(shell ls tests/aritmeticas*.alf | xargs | sed 's/.alf//g' | sed 's/$(DIRTESTS)\///g')
TESTS_INPUT=$(TESTS_ARIT)
TESTS_NOINPUT=
TESTS=$(TESTS_INPUT) $(TESTS_NOINPUT)
TESTS_ARIT_PER= _1 _2 _3

RED   := $(shell tput -Txterm setaf 1)
GREEN := $(shell tput -Txterm setaf 2)
RESET := $(shell tput -Txterm sgr0)

all: $(MAIN)

lex: $(MAIN).h y.tab.h alfa.l
	$(FLEX) alfa.l

bison: $(MAIN).h alfa.y
	$(BISON) alfa.y

$(MAIN): bison lex
	$(CC) $(CFLAGS) -o $@ lex.yy.c y.tab.c generacion.c tablahash.c tablasimbolos.c $@.c

ejemplo%: $(MAIN) $(DIREJEMPLOS)/entrada_sin_%.txt
	@echo - $@:
	-./$(MAIN) $(DIREJEMPLOS)/entrada_sin_$*.txt ejemplo_$*.asm
	@echo

ejemplo%_exec: ejemplo%
	$(NASM) ejemplo_$*.o $(NASMFLAGS) ejemplo_$*.asm
	$(CC) $(CFLAGS) -m32 -o ejemplo_$* ejemplo_$*.o alfalib.o

compare_ejemplos: $(EJEMPLOS)

#test: test_aritmeticas test_comparaciones test_error test_funciones test_if \
#		test_logicas test_vectores test_while
$(TESTS): $(MAIN)
	./$(MAIN) $(DIRTESTS)/$@.alf $(DIRTESTS)/$@.asm
	$(NASM) $(DIRTESTS)/$@.o $(NASMFLAGS) $(DIRTESTS)/$@.asm
	$(CC) $(CFLAGS) -m32 -o $(DIRTESTS)/$@ $(DIRTESTS)/$@.o alfalib.o

test_aritmeticas: $(TESTS_ARIT)
	@echo $(TESTS)
	$(foreach test, $(TESTS_ARIT),\
		$(foreach subtest, $(shell ls "$(DIRTESTS)/$(test)"*".input" | xargs | sed 's/$(DIRTESTS)\/$(test)_//g' | sed 's/.input//g'),\
		$(shell cat $(DIRTESTS)/$(test)_$(subtest).input | ./$(DIRTESTS)/$(test) >	$(DIRTESTS)/$(test)_$(subtest)output.test; \
			diff -Bb $(DIRTESTS)/$(test)_$(subtest).output $(DIRTESTS)/$(test)_$(subtest)output.test))\
		 )

clean:
	rm -f lex.yy.c y.* $(MAIN) misalida* ejemplo_* $(DIRTESTS)/*.asm $(DIRTESTS)/*output.test $(DIRTESTS)/*.o

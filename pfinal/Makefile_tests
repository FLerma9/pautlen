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
TESTS_COMP:=$(shell ls tests/comparaciones*.alf | xargs | sed 's/.alf//g' | sed 's/$(DIRTESTS)\///g')
TESTS_FUNCIONES_INPUT= funciones2
TESTS_FUNCIONES_NO_INPUT = funciones1 funciones3 funciones4
TESTS_IF_INPUT = if3
TESTS_IF_NO_INPUT = if1 if2
TESTS_LOGIC:=$(shell ls tests/logicas*.alf | xargs | sed 's/.alf//g' | sed 's/$(DIRTESTS)\///g')
TESTS_VECTOR:=$(shell ls tests/vectores*.alf | xargs | sed 's/.alf//g' | sed 's/$(DIRTESTS)\///g')
TESTS_WHILE:=$(shell ls tests/while*.alf | xargs | sed 's/.alf//g' | sed 's/$(DIRTESTS)\///g')
TESTS_ERROR:=$(shell ls tests/error_*.alf | xargs | sed 's/.alf//g' | sed 's/$(DIRTESTS)\///g')

TESTS_CUSTOM_INPUT:=$(shell ls tests/custom*.alf | xargs | sed 's/.alf//g' | sed 's/$(DIRTESTS)\///g')

TESTS_INPUT=$(TESTS_ARIT) $(TESTS_FUNCIONES_INPUT) $(TESTS_IF_INPUT) $(TESTS_LOGIC) $(TESTS_WHILE) $(TESTS_CUSTOM_INPUT)
TESTS_NOINPUT=$(TESTS_COMP) $(TESTS_FUNCIONES_NO_INPUT) $(TESTS_IF_NO_INPUT) $(TESTS_VECTOR)
TESTS=$(TESTS_INPUT) $(TESTS_NOINPUT) $(TESTS_ERROR)
TESTS_WITH_DIR:= $(addprefix $(DIRTESTS)/,$(TESTS))


RED   := $(shell tput -Txterm setaf 1)
GREEN := $(shell tput -Txterm setaf 2)
RESET := $(shell tput -Txterm sgr0)

all: $(MAIN)

lex: $(MAIN).h y.tab.h alfa.l
	$(FLEX) alfa.l

bison: $(MAIN).h alfa.y
	$(BISON) alfa.y

$(MAIN): bison lex
	@echo $(TESTS_ERROR)
	$(CC) $(CFLAGS) -o $@ lex.yy.c y.tab.c generacion.c tablahash.c tablasimbolos.c $@.c

ejemplo%: $(MAIN) $(DIREJEMPLOS)/entrada_sin_%.txt
	@echo - $@:
	-./$(MAIN) $(DIREJEMPLOS)/entrada_sin_$*.txt ejemplo_$*.asm
	@echo

ejemplo%_exec: ejemplo%
	$(NASM) ejemplo_$*.o $(NASMFLAGS) ejemplo_$*.asm
	$(CC) $(CFLAGS) -m32 -o ejemplo_$* ejemplo_$*.o alfalib.o

compare_ejemplos: $(EJEMPLOS)

test_all: test_aritmeticas test_logicas test_vectores test_comparaciones \
		test_if test_while test_funciones

test_aritmeticas: $(TESTS_ARIT)
test_comparaciones: $(TESTS_COMP)
test_funciones:	$(TESTS_FUNCIONES_INPUT) $(TESTS_FUNCIONES_NO_INPUT)
test_if: $(TESTS_IF_NO_INPUT) $(TESTS_IF_INPUT)
test_logicas: $(TESTS_LOGIC)
test_vectores: $(TESTS_VECTOR)
test_while: $(TESTS_WHILE)

test_errores: $(TESTS_ERROR)

$(TESTS_WITH_DIR): $(MAIN)
	./$(MAIN) $@.alf $@.asm > /dev/null
	$(NASM) $@.o $(NASMFLAGS) $@.asm > /dev/null
	$(CC) $(CFLAGS) -m32 -o $@ $@.o alfalib.o > /dev/null

$(TESTS_INPUT): %: $(DIRTESTS)/%
	$(foreach input_n, $(shell ls "$(DIRTESTS)/$@"*".input" | xargs | sed 's/$(DIRTESTS)\/$@//g' | sed 's/.input//g'),\
		$(shell cat $(DIRTESTS)/$@$(input_n).input | ./$(DIRTESTS)/$@ >	$(DIRTESTS)/$@$(input_n).output.test;\
		diff -Bb $(DIRTESTS)/$@$(input_n).output $(DIRTESTS)/$@$(input_n).output.test))
	@echo "${GREEN}$@${RESET}"

$(TESTS_NOINPUT): %: $(DIRTESTS)/%
	$(shell ./$(DIRTESTS)/$@ >	$(DIRTESTS)/$@.output.test;\
	diff -Bb $(DIRTESTS)/$@.output $(DIRTESTS)/$@.output.test)
	@echo "${GREEN}$@${RESET}"

$(TESTS_ERROR): %: $(DIRTESTS)/%
	@echo "${GREEN}$@${RESET}"
	-./$(DIRTESTS)/$@;

clean: clean_tests
	rm -f lex.yy.c y.* $(MAIN) misalida* ejemplo_*
clean_tests:
	rm -f $(DIRTESTS)/*.asm $(DIRTESTS)/*output.test $(DIRTESTS)/*.o $(TESTS_WITH_DIR)

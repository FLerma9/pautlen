.PHONY: clean all

MAIN=alfa
EJEMPLOS=ejemplo1 ejemplo2 ejemplo3
DIREJEMPLOS=ejemplos
FLEX=flex
BISON=bison $(BFLAGS)
BFLAGS=-d -y -v

all: $(MAIN)

lex: $(MAIN).h y.tab.h alfa.l 
	$(FLEX) alfa.l

bison: $(MAIN).h alfa.y
	$(BISON) alfa.y

$(MAIN): bison lex
	gcc -Wall -o $@ lex.yy.c y.tab.c generacion.c tablahash.c tablasimbolos.c $@.c 

ejemplo%: $(DIREJEMPLOS)/entrada_sin_%.txt
	@echo - $@:
	-./$(MAIN) $(DIREJEMPLOS)/entrada_sin_$*.txt misalida_sin_$*.txt
	@echo 


compare_ejemplos: $(EJEMPLOS)


clean:
	rm -f lex.yy.c y.* $(MAIN) misalida*
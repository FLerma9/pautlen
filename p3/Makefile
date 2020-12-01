.PHONY: clean all

MAIN=pruebaSintactico
EJEMPLOS=ejemplo1 ejemplo2 ejemplo3
DIREJEMPLOS=ejemplos
FLEX=flex
BISON=bison $(BFLAGS)
BFLAGS=-d -y -v

all: bison lex $(MAIN)

lex: $(MAIN).h y.tab.h alfa.l 
	$(FLEX) alfa.l

bison: $(MAIN).h alfa.y
	$(BISON) alfa.y

$(MAIN):
	gcc -Wall -o $@ lex.yy.c y.tab.c $@.c

compare_ejemplos: $(EJEMPLOS)

ejemplo%: $(DIREJEMPLOS)/entrada_sin_%.txt
	@echo - $@:
	-./$(MAIN) $(DIREJEMPLOS)/entrada_sin_$*.txt misalida_sin_$*.txt
	@echo - Diferencia con salida$* original:
	diff -Bb $(DIREJEMPLOS)/salida_sin_$*.txt misalida_sin_$*.txt
	@echo 

clean:
	rm -f lex.yy.c y.* $(MAIN) misalida*
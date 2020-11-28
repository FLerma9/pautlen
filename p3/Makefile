.PHONY: clean all

EJEMPLOS=ejemplo1 ejemplo2 ejemplo3
DIREJEMPLOS=ejemplos
EXEC=pruebaSintactico
FLEX=flex
BISON=bison $(BFLAGS)
BFLAGS=-d -y -v

all: bison lex
	gcc -Wall -o $(EXEC) lex.yy.c y.tab.c flexbison.c

lex: y.tab.h alfa.l
	$(FLEX) alfa.l

bison: alfa.y
	$(BISON) alfa.y

compare_ejemplos: $(EJEMPLOS)

ejemplo%: $(DIREJEMPLOS)/entrada_sin_%.txt
	@echo - $@:
	./$(EXEC) $(DIREJEMPLOS)/entrada_sin_$*.txt misalida_sin_$*.txt
	@echo - Diferencia con salida$* original:
	diff -Bb $(DIREJEMPLOS)/salida_sin_$*.txt misalida_sin_$*.txt
	@echo 

clean:
	rm -f lex.yy.c y.* $(EXEC) misalida*
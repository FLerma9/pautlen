.PHONY: clean all

EJEMPLOS=ejemplo1 ejemplo2 ejemplo3
DIREJEMPLOS=ejemplos
EXEC=pruebaMorfo

all: tokens.h alfa.l
	flex alfa.l
	gcc -Wall -o $(EXEC) lex.yy.c

compare_ejemplos: $(EJEMPLOS)

ejemplo%: $(DIREJEMPLOS)/entrada%.txt
	@echo - $@:
	./$(EXEC) $(DIREJEMPLOS)/entrada$*.txt misalida$*.txt
	@echo - Diferencia con salida$* original:
	diff -Bb $(DIREJEMPLOS)/salida$*.txt misalida$*.txt
	@echo 

clean:
	rm -f lex.yy.c $(EXEC) misalida*
.PHONY: clean all

CC = gcc
CFLAGS = -Wall -g
EXEC = prueba_tabla
FICHEROENTRADA = prueba.txt
FICHEROSALIDA = salida.txt

all: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) -o $(EXEC) $(EXEC).c tablahash.c tablasimbolos.c

run: $(EXEC)
	./$(EXEC) $(FICHEROENTRADA) $(FICHEROSALIDA)

clean:
	rm -f $(EXEC) $(FICHEROSALIDA)

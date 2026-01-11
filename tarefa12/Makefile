CFLAGS = -std=c99 -Wall -Werror -Wvla -g

LDFLAGS = -lm

TARGET = centros

SRC = centros.o grafos.o hash.o fila_de_prioridades.o cliente.o

OBJ = centros.o grafos.o hash.o fila_de_prioridades.o cliente.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(OBJ) $(LDFLAGS) -o $(TARGET)

centros.o: centros.c centros.h
	gcc $(CFLAGS) -c centros.c -o centros.o

grafos.o: grafos.c centros.h
	gcc $(CFLAGS) -c grafos.c -o grafos.o

hash.o: hash.c centros.h
	gcc $(CFLAGS) -c hash.c -o hash.o

fila_de_prioridades.o: fila_de_prioridades.c centros.h
	gcc $(CFLAGS) -c fila_de_prioridades.c -o fila_de_prioridades.o


cliente.o: cliente.c centros.h
	gcc $(CFLAGS) -c cliente.c -o cliente.o

clean:
	rm -f $(OBJ) $(TARGET)

CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cidades

cidades: cliente.o cidades.o
	gcc cliente.o cidades.o $(LDFLAGS) -o cidades

cliente.o: cliente.c cidades.h
	gcc $(CFLAGS) -c cliente.c


cidades.o: cidades.c cidades.h
	gcc $(CFLAGS) -c cidades.c


clean:
	rm -f cliente.o cidades.o cidades
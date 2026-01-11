CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: improbabilidade

improbabilidade: cliente.o improbabilidade.o
	gcc cliente.o improbabilidade.o $(LDFLAGS) -o improbabilidade

cliente.o: cliente.c improbabilidade.h
	gcc $(CFLAGS) -c cliente.c


improbabilidade.o: improbabilidade.c improbabilidade.h
	gcc $(CFLAGS) -c improbabilidade.c


clean:
	rm -f cliente.o improbabilidade.o improbabilidade
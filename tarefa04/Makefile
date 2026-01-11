CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: batcomputador

batcomputador: batcomputador.c
	gcc $(CFLAGS) batcomputador.c -o batcomputador $(LDFLAGS)

clean:
	rm -f batcomputador

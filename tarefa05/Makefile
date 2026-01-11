CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: sequencia

sequencia: sequencia.c
	gcc $(CFLAGS) sequencia.c -o sequencia $(LDFLAGS)

clean:
	rm -f sequencia

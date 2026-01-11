CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: otimizar

otimizar: otimizar.c
	gcc $(CFLAGS) otimizar.c -o otimizar $(LDFLAGS)

clean:
	rm -f otimizar

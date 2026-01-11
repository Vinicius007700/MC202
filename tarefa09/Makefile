CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cache

cache: cliente.o cache.o
	gcc cliente.o cache.o $(LDFLAGS) -o cache

cliente.o: cliente.c cache.h
	gcc $(CFLAGS) -c cliente.c


cache.o: cache.c cache.h
	gcc $(CFLAGS) -c cache.c


clean:
	rm -f cliente.o cache.o cache
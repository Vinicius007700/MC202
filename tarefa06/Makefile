CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cobra

cobra: cliente.o cobra.o
	gcc cliente.o cobra.o $(LDFLAGS) -o cobra

cliente.o: cliente.c cobra.h
	gcc $(CFLAGS) -c cliente.c


cobra.o: cobra.c cobra.h
	gcc $(CFLAGS) -c cobra.c


clean:
	rm -f cliente.o cobra.o cobra
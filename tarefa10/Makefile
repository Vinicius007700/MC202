CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: cliente.o corretor.o
	gcc cliente.o corretor.o $(LDFLAGS) -o corretor

cliente.o: cliente.c corretor.h
	gcc $(CFLAGS) -c cliente.c


corretor.o: corretor.c corretor.h
	gcc $(CFLAGS) -c corretor.c


clean:
	rm -f cliente.o corretor.o corretor
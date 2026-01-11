CFLAGS = -std=c99 -Wall -Werror -Wvla -g

LDFLAGS = -lm

TARGET = piscapisca

SRC = info_led.c grafo.c cliente.c

OBJ = info_led.o grafo.o cliente.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(OBJ) $(LDFLAGS) -o $(TARGET)

info_led.o: info_led.c piscapisca.h
	gcc $(CFLAGS) -c info_led.c -o info_led.o

grafo.o: grafo.c piscapisca.h
	gcc $(CFLAGS) -c grafo.c -o grafo.o

cliente.o: cliente.c piscapisca.h
	gcc $(CFLAGS) -c cliente.c -o cliente.o

clean:
	rm -f $(OBJ) $(TARGET)

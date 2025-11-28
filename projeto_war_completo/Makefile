CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: novato aventureiro mestre

novato: novato.c
	$(CC) $(CFLAGS) -o novato novato.c

aventureiro: aventureiro.c
	$(CC) $(CFLAGS) -o aventureiro aventureiro.c

mestre: mestre.c
	$(CC) $(CFLAGS) -o mestre mestre.c

clean:
	rm -f novato aventureiro mestre

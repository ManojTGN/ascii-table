CC = gcc
BINS = main

all: $(BINS)

main:
	$(CC) -o build/ascii.exe src/main.c

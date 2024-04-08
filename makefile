CC = gcc
BINS = main

all: $(BINS)

main:
	if not exist build mkdir build
	$(CC) -o build/ascii.exe src/main.c

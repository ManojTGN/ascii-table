CC = gcc
BINS = main

all: $(BINS)

main:
	@if [ ! -d "build" ]; then mkdir build; fi
	$(CC) -o build/ascii.exe src/main.c

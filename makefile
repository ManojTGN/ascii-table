CC    = gcc
BINS = _build

all: $(BINS)

_test: build
	$(CC) -o test/test.exe build/ascii.o test/test.c

_build:
	
	$(CC) -o build/ascii.o -c src/ascii.c
	$(CC) -o build/ascii.exe build/ascii.o src/main.c

clean:
	rm -rf "./build/*.o"

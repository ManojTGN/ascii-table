CC    = gcc
BINS = _build

all: $(BINS)

_test: _build
	$(CC) -o test/test.exe build/ascii.o test/test.c
	./test/test.exe

_build:
	if [ ! -d build ]; then mkdir build; fi
	$(CC) -o build/ascii.o -c src/ascii.c
	$(CC) -o build/ascii.exe build/ascii.o src/main.c

clean:
	rm -rf "./build/*.o"
	rm -rf "./build/*.exe"

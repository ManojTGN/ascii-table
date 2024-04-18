CC    = gcc
CXX   = g++
BINS = _build

all: $(BINS)

_test: _build
	$(CC) -o test/test.exe build/ascii.o test/test.c
	./test/test.exe

table:
	$(CXX) -shared -o build/table.dll src/tablePartial.cpp 
	$(CC) -o build/table.o -c src/table.c

_build: clean table
	if [ ! -d build ]; then mkdir build; fi
	$(CC) -o build/ascii.o -c src/ascii.c
	$(CC) -o build/ascii.exe build/ascii.o build/table.o src/main.c -Lbuild -ltable

clean:
	rm -rf build/*.o
	rm -rf build/*.exe
	rm -rf build/*.dll

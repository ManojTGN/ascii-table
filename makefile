CC    = gcc
CXX   = g++
BINS = _build

all: $(BINS)

_test: _build
	$(CC) -o test/test.exe build/ascii.o test/test.c
	./test/test.exe

rc:
	if [ ! -d build ]; then mkdir build; fi
	windres ascii.rc -o build/asciirc.o

renderer:
	if [ ! -d build ]; then mkdir build; fi
	$(CXX) -shared -o build/renderer.dll src/renderer.cpp -Wno-write-strings

_build: clean renderer rc
	if [ ! -d build ]; then mkdir build; fi
	$(CC) -o build/ascii.o -c src/ascii.c
	$(CC) -o build/ascii.exe build/ascii.o src/main.c -Lbuild -lrenderer build/asciirc.o

clean:
	if [ ! -d build ]; then mkdir build; fi
	rm -rf build/*.o
	rm -rf build/*.exe
	rm -rf build/*.dll

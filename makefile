CC = gcc
BINS = main test clean

all: $(BINS)

main:
	$(CC) -o build/ascii.exe src/main.c

test:
	$(CC) src/test.c -c

# `clean` is not needed 
clean:
	rm -f build/*.o
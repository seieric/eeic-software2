CC = gcc
TARGET = bin/qsort

$(TARGET): lib/libinteger.a
	$(CC) -o $(TARGET) -L./lib -I./include src/main.c -linteger

lib/libinteger.a: src/initlib.o
	ar rsv lib/libinteger.a src/initlib.o

src/initlib.o:
	$(CC) initlib.c

.PHONY: clean
clean:
	rm -rf bin/* lib/*
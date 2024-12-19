CC = gcc
TARGET = calc

$(TARGET): main.o vector.o matrix.o
	$(CC) -o calc main.o vector.o matrix.o

.PHONY: clean
clean:
	rm *.o a.out
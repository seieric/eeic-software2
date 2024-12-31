CC = gcc
TARGET = fibo
OBJS = fibo.o main.o

$(TARGET): $(OBJS)
	$(CC) -Wall -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
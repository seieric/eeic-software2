CC = gcc

BINDIR = ./bin
INCLUDE = ./include
SRCDIR = ./src

CFLAGS = -Wall -I$(INCLUDE) 
LDFLAGS = -lm

OBJS = $(SRCDIR)/adv_regression.o $(SRCDIR)/matrix.o $(SRCDIR)/activation.o $(SRCDIR)/data.o $(SRCDIR)/criterion.o

TARGET = $(BINDIR)/nn

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET)
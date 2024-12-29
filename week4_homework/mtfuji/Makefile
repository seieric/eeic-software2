CC = gcc

BINDIR = ./bin
INCLUDE = ./include
SRCDIR = ./src

CFLAGS = -Wall -I$(INCLUDE) 
LDFLAGS = -lm

OBJS = $(SRCDIR)/mtfuji.o $(SRCDIR)/func.o $(SRCDIR)/data.o $(SRCDIR)/optimize.o

TARGET = $(BINDIR)/mtfuji

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET)
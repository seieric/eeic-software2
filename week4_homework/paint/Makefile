CC = gcc

BINDIR = ./bin
INCLUDE = ./include
LIBDIR = ./lib
SRCDIR = ./src

CFLAGS = -Wall -I$(INCLUDE) 
LDFLAGS = -L$(LIBDIR)

#LDLIBS = -linteger 

SRC = $(SRCDIR)/paintapp.c
OBJS = $(SRCDIR)/paintapp.o $(SRCDIR)/canvas.o $(SRCDIR)/display.o $(SRCDIR)/history.o
#LIB = $(LIBDIR)/libinteger.a

TARGET = $(BINDIR)/paintapp

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm *.o *~ a.out
CC = gcc

BINDIR = ./bin
INCLUDE = ./include
LIBDIR = ./lib
SRCDIR = ./src

CFLAGS = -Wall -I$(INCLUDE) 
LDFLAGS = -L$(LIBDIR)

#LDLIBS = -linteger 

SRC = $(SRCDIR)/paintapp.c
OBJS = $(SRCDIR)/canvas.o $(SRCDIR)/paintapp.o
#LIB = $(LIBDIR)/libinteger.a

TARGET = $(BINDIR)/paintapp

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm *.o *~ a.out
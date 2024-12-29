CC = gcc

BINDIR = ./bin
INCLUDE = ./include
LIBDIR = ./lib
SRCDIR = ./src

CFLAGS = -Wall -I$(INCLUDE) 
LDFLAGS = -L$(LIBDIR)

#LDLIBS = -linteger 

SRC = $(SRCDIR)/paintapp.c
#OBJ = $(SRCDIR)/intlib.o
#LIB = $(LIBDIR)/libinteger.a

TARGET = $(BINDIR)/paintapp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	rm *.o *~ a.out
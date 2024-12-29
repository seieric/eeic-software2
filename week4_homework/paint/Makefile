CC = gcc

BINDIR = ./bin
INCLUDE = ./include
LIBDIR = ./lib
SRCDIR = ./src

CFLAGS = -Wall -I$(INCLUDE) 
LDFLAGS = -L$(LIBDIR)

LDLIBS = -lhistory

SRC = $(SRCDIR)/paintapp.c
OBJS = $(SRCDIR)/paintapp.o $(SRCDIR)/canvas.o $(SRCDIR)/display.o
LIBS = $(LIBDIR)/libhistory.a

TARGET = $(BINDIR)/paintapp

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBS): $(SRCDIR)/history.o
	$(AR) rsv $@ $^

.PHONY: clean
clean:
	rm $(OBJS) $(LIBS) $(TARGET) $(SRCDIR)/history.o
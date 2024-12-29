CC = gcc

BINDIR = ./bin
INCLUDE = ./include
LIBDIR = ./lib
SRCDIR = ./src

CFLAGS = -Wall -I$(INCLUDE) 
LDFLAGS = -L$(LIBDIR)

SRC = $(SRCDIR)/paintapp.c
OBJS = $(SRCDIR)/paintapp.o $(SRCDIR)/canvas.o $(SRCDIR)/display.o

TARGET = $(BINDIR)/paintapp

$(TARGET): $(OBJS) $(LIBDIR)/libhistory.a
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: array
array: $(OBJS) $(LIBDIR)/libhistory_array.a
	$(CC) $(CFLAGS) -o $(BINDIR)/paintapp_array $^

$(LIBDIR)/libhistory.a: $(SRCDIR)/history.o
	$(AR) rsv $@ $^

$(LIBDIR)/libhistory_array.a: $(SRCDIR)/history_array.o
	$(AR) rsv $@ $^

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET) $(SRCDIR)/history.o $(SRCDIR)/history_array.o $(BINDIR)/paintapp_array $(LIBDIR)/libhistory.a $(LIBDIR)/libhistory_array.a
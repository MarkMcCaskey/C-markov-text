TARGET = markov_text
LIBS = 
CC = gcc
CFLAGS = -g -Wall

srcdir = src/
incdir = inc/
builddir = build/

.PHONY: clean all default

HEADERS = prefixtree.h error.h
OBJECTS = main.o prefixtree.o error.o

default: $(TARGET)
all: default

%.o: %.c $(incdir)$(HEADERS)
	$(CC) $(CFLAGS) -c $(srcdir)$< -o $(builddir)$@

.PRECIOUS: $(TARGET) $(builddir)$(OBJECTS)

$(TARGET): $(builddir)$(OBJECTS)
	$(CC) $(builddir)$(OBJECTS) $(CFLAGS) $(LIBS) -o $(builddir)$@

clean:
	-rm -f $(builddir)*.o
	-rm -f $(TARGET)

TARGET = markov_text
LIBS = 
CC = gcc
CFLAGS = -g -Wall

.PHONY: clean all default

HEADERS = prefixtree.h error.h
OBJECTS = main.o prefixtree.o error.o

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

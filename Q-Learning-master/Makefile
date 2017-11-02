CC = g++
CFLAGS=-c -w -O2
SOURCES=main.cpp utils/utils.cpp utils/utils.h
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=qlearn

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *o qlearn
	rm -rf qlearn.txt

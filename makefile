CC = gcc
CCFLAGS = -Wall -g -o 
SOURCES = $(wildcard *.c)
OUTPUT = compiler

all:
	$(CC) $(CCFLAGS) $(OUTPUT) $(SOURCES)

clean:
	rm -rf $(OUTPUT) *.*~ *~

run:
	./$(OUTPUT)

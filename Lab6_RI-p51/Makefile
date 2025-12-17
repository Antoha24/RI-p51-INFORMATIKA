# Makefile for simple program with math library
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = main
SOURCES = main.c lib.c
OBJECTS = $(SOURCES:.c=.o)

# Main target - link object files
$(TARGET): $(OBJECTS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lm

# Compile object files
main.o: main.c lib.h
    $(CC) $(CFLAGS) -c main.c

lib.o: lib.c lib.h
    $(CC) $(CFLAGS) -c lib.c

# Run program
run: $(TARGET)
    ./$(TARGET)

# Clean build files
clean:
    rm -f $(TARGET) $(OBJECTS)

# View structure
view:
    @echo "=== Build info ==="
    @echo "Compiler: $(CC)"
    @echo "Flags: $(CFLAGS)"
    @echo "Target: $(TARGET)"
    @echo "Sources: $(SOURCES)"

.PHONY: clean run view

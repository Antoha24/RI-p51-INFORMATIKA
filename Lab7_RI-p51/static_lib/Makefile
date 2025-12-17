# Makefile for static library build
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -DSTATIC
TARGET = main
LIBRARY = libstatic.a
SOURCES = main.c lib.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build static library
$(LIBRARY): lib.o
    ar rcs $(LIBRARY) lib.o

# Link main program with static library
$(TARGET): main.o $(LIBRARY)
    $(CC) $(CFLAGS) -o $(TARGET) main.o $(LIBRARY) -lm

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
    rm -f $(TARGET) $(LIBRARY) $(OBJECTS)

# View build info
view:
    @echo "=== Build info (Static) ==="
    @echo "Compiler: $(CC)"
    @echo "Flags: $(CFLAGS)"
    @echo "Target: $(TARGET)"
    @echo "Library: $(LIBRARY)"

.PHONY: all clean run view

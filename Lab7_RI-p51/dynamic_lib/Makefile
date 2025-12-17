# Makefile for dynamic library build
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -fPIC
TARGET = main
LIBRARY = libdynamic.so
SOURCES = main.c lib.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build dynamic library
$(LIBRARY): lib.o
    $(CC) -shared -o $(LIBRARY) lib.o

# Link main program with dynamic library
$(TARGET): main.o $(LIBRARY)
    $(CC) $(CFLAGS) -o $(TARGET) main.o ./$(LIBRARY) -lm

# Compile object files
main.o: main.c lib.h
    $(CC) $(CFLAGS) -c main.c

lib.o: lib.c lib.h
    $(CC) $(CFLAGS) -c lib.c

# Run program
run: $(TARGET)
    LD_LIBRARY_PATH=. ./$(TARGET)

# Clean build files
clean:
    rm -f $(TARGET) $(LIBRARY) $(OBJECTS)

# View build info
view:
    @echo "=== Build info (Dynamic) ==="
    @echo "Compiler: $(CC)"
    @echo "Flags: $(CFLAGS)"
    @echo "Target: $(TARGET)"
    @echo
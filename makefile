# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Libraries
LIBS = -lSDL -lSDL_image -lm

# Source files
SRCS = entity.c main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = prog

# Make all
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Compiling .c files to .o files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean
clean:
	rm -f $(OBJS) $(TARGET)

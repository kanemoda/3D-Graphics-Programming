# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lm

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
TARGET = renderer

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Run the program after building
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean run

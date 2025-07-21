# Makefile

# Compiler and flags
CXX := g++.exe
CXXFLAGS := -g -std=c++17 -Iinclude

# Source files
SRC := src/main.cpp src/glad.c src/game.cpp src/resource_manager.cpp src/shader.cpp src/texture.cpp src/sprite_renderer.cpp

# Output
BIN_DIR := bin
TARGET := $(BIN_DIR)/main.exe

# Libraries
LIBS := -Llib/GLFW -lopengl32 -lglfw3 -lgdi32

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean target
clean:
	rm -rf $(BIN_DIR)

# Run the executable (optional)
run: $(TARGET)
	./$(TARGET)

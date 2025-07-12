# Makefile for C++ project with C++11 standard

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude

# Name of the executable output
TARGET = main

# Source files directory
SRC_DIR = src

# Object files directory
OBJ_DIR = obj

# Find cpp source files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Replace source directory with object directory in object file paths
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link all object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Make sure the object directory exists
$(OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build files
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
	rmdir $(OBJ_DIR)

.PHONY: all clean

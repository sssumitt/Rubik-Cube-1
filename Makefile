# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(INCLUDE_DIR)

# -fsanitize=undefined -g -Og

# Source files and output
SRC_DIR = src
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/Cube.cpp $(SRC_DIR)/CoordCube.cpp $(SRC_DIR)/FaceCube.cpp $(SRC_DIR)/MoveTable.cpp $(SRC_DIR)/pruneTable.cpp $(SRC_DIR)/Search.cpp $(SRC_DIR)/main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = cube_solver.exe

# Declare phony targets
.PHONY: all clean

# Default target to build the executable
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	@del /Q $(SRC_DIR)\*.o $(TARGET)

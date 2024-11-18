# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# List of object files
OBJ = main.o \
      player/Player.o \
      enemy/Enemy.o enemy/Dragon.o \
      inventory/Storage.o inventory/Ammo.o \
      utilities/GridUtils.o

# Output executable
TARGET = game

# Default target to build the executable
all: $(TARGET)

# Linking the object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

# Rebuild the project
rebuild: clean all

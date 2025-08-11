# Makefile for whale_market project
# Compatible with make on Windows 11

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude
LDFLAGS = 

# Directories
SRCDIR = src
INCDIR = include
CLASSDIR = src/class
TOOLSDIR = src/tools

# Source files
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/menu.cpp $(CLASSDIR)/admin.cpp $(CLASSDIR)/good.cpp $(CLASSDIR)/user.cpp $(CLASSDIR)/order.cpp $(TOOLSDIR)/color.cpp
OBJECTS = main.o menu.o admin.o good.o user.o order.o color.o

# Target executable
TARGET = main.exe

# Default target
all: $(TARGET)

# Build target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o main.o

menu.o: $(SRCDIR)/menu.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/menu.cpp -o menu.o

admin.o: $(CLASSDIR)/admin.cpp
	$(CXX) $(CXXFLAGS) -c $(CLASSDIR)/admin.cpp -o admin.o

good.o: $(CLASSDIR)/good.cpp
	$(CXX) $(CXXFLAGS) -c $(CLASSDIR)/good.cpp -o good.o

user.o: $(CLASSDIR)/user.cpp
	$(CXX) $(CXXFLAGS) -c $(CLASSDIR)/user.cpp -o user.o

order.o: $(CLASSDIR)/order.cpp
	$(CXX) $(CXXFLAGS) -c $(CLASSDIR)/order.cpp -o order.o

color.o: $(TOOLSDIR)/color.cpp
	$(CXX) $(CXXFLAGS) -c $(TOOLSDIR)/color.cpp -o color.o

# Clean build artifacts
clean:
	rm -f *.o

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: rebuild

# Show help
help:
	@echo Available targets:
	@echo   all      - Build the project (default)
	@echo   clean    - Remove build artifacts
	@echo   rebuild  - Clean and build
	@echo   run      - Build and run the program
	@echo   debug    - Build with debug information
	@echo   help     - Show this help message

.PHONY: all clean rebuild run help debug
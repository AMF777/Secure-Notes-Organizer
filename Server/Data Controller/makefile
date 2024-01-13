# Makefile for Connector program

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -I/usr/include/cppconn

# Linker flags
LDFLAGS = -L/usr/lib -lmysqlcppconn

# Target executable
TARGET = DataController

# Source files
SOURCES = DataController.cpp main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all run clean
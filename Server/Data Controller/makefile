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
SOURCES = DataController.cpp main.cpp User.cpp Note.cpp NoteComponent.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = User.h Note.h DataController.h NoteComponent.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all run clean

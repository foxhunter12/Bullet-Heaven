CXX = g++
TARGET = bulletheaven

CXXFLAGS = -std=c++11 -g -O2 -Wall -Wno-reorder
CPPFLAGS = -I../SFML-2.3.2/include
LDFLAGS = -L../SFML-2.3.2/lib
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

OBJECTS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: default all clean

default: $(TARGET)

all: default

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
        $(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
        -rm -rf $(OBJECTS) $(TARGET)

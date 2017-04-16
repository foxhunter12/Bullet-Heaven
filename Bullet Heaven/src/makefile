CXX = g++
TARGET = BulletHeaven

CXXFLAGS = -std=c++14 -g -O2 -Wall -Wno-reorder
LDFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
OBJECTS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: default all clean

default: $(TARGET)

all: default

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-rm -rf $(OBJECTS) $(TARGET)

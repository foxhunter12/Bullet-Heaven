CXX = g++
TARGET = BulletHeaven

CXXFLAGS = -I../SFML-2.3.2/include -std=c++14 -g -O2 -Wall -Wno-reorder
LDFLAGS = -L../SFML-2.3.2/lib -L../SFML-2.3.2/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
LD_LIBRARY_PATH := ../SFML-2.3.2/lib
OBJECTS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: default all clean

default: $(TARGET)

all: default

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-rm -rf $(OBJECTS) $(TARGET)

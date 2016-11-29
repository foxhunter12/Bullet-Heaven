CXX = g++
TARGET = BulletHeaven

CXXFLAGS = -std=c++11 -g -O2 -Wall -Wno-reorder
CPPFLAGS = -I../SFML-2.3.2/include
LDFLAGS = -L../SFML-2.3.2/lib
LD_LIBRARY_PATH := ../SFML-2.3.2/lib
INCLUDES := -I../SFML-2.3.2/include
LIBS = -L../SFML-2.3.2/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

OBJECTS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: default all clean

default: $(TARGET)

all: default

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) $(LIBS) -o $@ $^

clean:
	-rm -rf $(OBJECTS) $(TARGET)

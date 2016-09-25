CXX := g++

TARGET := bulletheaven

LD_LIBRARY_PATH := ../SFML-2.3.2/lib
 
CXXFLAGS := -std=c++11 -g -Wall -Wno-reorder
 
LIBS := -L../SFML-2.3.2/lib -Isfml-graphics -Isfml-audio -Isfml-window -Isfml-system
 
INCLUDES := -I../SFML-2.3.2/include

OBJECTS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: default all clean

default: $(TARGET)

all: default

%.o: %.cpp $(LIBS) $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) -g -Wall -Wno-reorder -c $(CXXFLAGS) $(LIBS) $(INCLUDES) -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)
 
$(TARGET): $(OBJECTS)
	@echo "** Building the game"
	$(CXX) -o ../BulletHeaven $(OBJECTS) $(CXXFLAGS) $(LIBS)
	@echo "** Done building"

clean:
	-rm -rf *.o
	-rm -rf $(TARGET)

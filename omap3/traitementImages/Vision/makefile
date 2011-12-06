CC=g++
CFLAGS=-c -Wall -g -O0 `pkg-config opencv --cflags`
LDFLAGS=`pkg-config opencv --libs`
SOURCES=Vision.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Vision.bin
all: $(SOURCES) $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
 
clean:
	rm *.o

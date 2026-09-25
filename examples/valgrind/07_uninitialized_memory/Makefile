CXX = g++
CXXFLAGS = -g -Wall

TARGET = uninitialized

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --track-origins=yes ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run valgrind clean

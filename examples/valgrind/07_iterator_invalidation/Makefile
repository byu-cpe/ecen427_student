CXX = g++
CXXFLAGS = -g -Wall

TARGET = iterator_invalid

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run valgrind clean

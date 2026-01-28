CXX = g++
CXXFLAGS = -g -Wall

TARGET = memory_leak

release: CXXFLAGS = -Wall -O2
release: $(TARGET)

debug: CXXFLAGS = -g -Wall
debug: $(TARGET)


$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: debug release run valgrind clean

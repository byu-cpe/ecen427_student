CC = gcc
CFLAGS = -Wall

TARGET = learn_mmap

$(TARGET): learn_mmap.c
	$(CC) $(CFLAGS) -o $@ $<

# Runs the program (which modifies hello.txt through the mapping), shows the
# file, then restores it so the next run starts fresh
run: $(TARGET)
	./$(TARGET)
	cat hello.txt
	printf "Hello World!" > hello.txt

# Same, under strace
trace: $(TARGET)
	strace ./$(TARGET)
	cat hello.txt
	printf "Hello World!" > hello.txt

clean:
	rm -f $(TARGET)

.PHONY: run trace clean

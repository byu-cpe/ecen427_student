CC = gcc
CFLAGS = -Wall -O2

TARGET = syscall

# Buffer size passed to the program.  Override on the command line:
#   make run BUF=1
BUF ?= 100

$(TARGET): syscall.c
	$(CC) $(CFLAGS) -o $@ $<

# Build and run
run: $(TARGET)
	./$(TARGET) $(BUF)

# Print every system call the program makes
trace: $(TARGET)
	strace ./$(TARGET) $(BUF)

# Print a table counting the system calls
summary: $(TARGET)
	strace --summary-only ./$(TARGET) $(BUF)

# Run with several buffer sizes to compare runtimes
compare: $(TARGET)
	@for b in 1 10 100 1000 10000 100000; do ./$(TARGET) $$b; done

clean:
	rm -f $(TARGET)

.PHONY: run trace summary compare clean

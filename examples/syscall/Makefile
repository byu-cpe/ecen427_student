CC = gcc
CFLAGS = -Wall -O2

TARGETS = syscall fread

# Which program to run (syscall or fread) and the buffer size to pass it.
# Override on the command line:
#   make run PROG=fread BUF=1
PROG ?= syscall
BUF ?= 100

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Build and run
run: $(PROG)
	./$(PROG) $(BUF)

# Print every system call the program makes
trace: $(PROG)
	strace ./$(PROG) $(BUF)

# Print a table counting the system calls
summary: $(PROG)
	strace --summary-only ./$(PROG) $(BUF)

# Run with several buffer sizes to compare runtimes
compare: $(PROG)
	@for b in 1 10 100 1000 10000 100000; do ./$(PROG) $$b; done

clean:
	rm -f $(TARGETS)

.PHONY: all run trace summary compare clean

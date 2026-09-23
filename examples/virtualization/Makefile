CC = gcc
CFLAGS = -Wall

TARGETS = cpu mem

all: $(TARGETS)

%: %.c common.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

.PHONY: all clean

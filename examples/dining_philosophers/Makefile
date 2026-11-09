CFLAGS = -O2 -Wall -pthread

all: philosophers_unsync philosophers_trylock

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f philosophers_unsync philosophers_trylock

.PHONY: all clean

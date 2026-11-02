CFLAGS = -O2 -Wall -pthread

all: philosophers_unsync philosophers_sync

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f philosophers_unsync philosophers_sync

.PHONY: all clean

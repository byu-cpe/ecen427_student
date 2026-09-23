# System Calls and Buffer Size

Two programs read `asyoulik.txt` (Shakespeare's *As You Like It*) and report
how many calls it took and how long it ran.  The buffer size is a command-line
argument, so you can see how the number of system calls affects runtime.

- `syscall.c` uses the `open()`, `read()`, and `close()` system calls
  directly.  Every `read()` is a trip into the kernel.
- `fread.c` does the same loop with `fopen()` and `fread()`.  These are C
  library functions, not system calls: `fread()` copies out of a 4 KB buffer
  inside the `FILE` struct and only calls `read()` when it runs dry.

## Build and run

```
make run              # syscall, default 100-byte buffer
make run BUF=1        # one byte per read()
make run BUF=4096
make compare          # run with several buffer sizes
make run PROG=fread BUF=1   # same loop through fread()
```

Add `-p` to echo the file to the terminal, which adds one `write()` call per
`read()`:

```
./syscall 4096 -p
```

## Watching the system calls

`strace` lists every system call a program makes.

```
make trace            # print each system call
make summary BUF=1    # count the system calls in a table
make summary PROG=fread BUF=1   # compare: a few dozen read() calls, not 125,000
```

## Key Lesson

Every system call switches from user mode to the kernel and back, which costs
far more than the work of copying a few bytes.  Reading one byte at a time
makes hundreds of thousands of system calls; reading a few kilobytes at a time
makes a handful.  This is why the C library buffers `fread()` and `printf()`
behind the scenes.

# System Calls and Buffer Size

Reads `asyoulik.txt` (Shakespeare's *As You Like It*) using the `open()`,
`read()`, and `close()` system calls, then reports how many `read()` calls it
took and how long it ran.  The buffer size given to `read()` is a command-line
argument, so you can see how the number of system calls affects runtime.

## Build and run

```
make run              # default 100-byte buffer
make run BUF=1        # one byte per read()
make run BUF=4096
make compare          # run with several buffer sizes
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
```

## Key Lesson

Every system call switches from user mode to the kernel and back, which costs
far more than the work of copying a few bytes.  Reading one byte at a time
makes hundreds of thousands of system calls; reading a few kilobytes at a time
makes a handful.  This is why the C library buffers `fread()` and `printf()`
behind the scenes.

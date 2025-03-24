CC=clang
CFLAGS=-Wall -g


BINS=forktest rawhello exec1 exec2 exec3 exec4 zombies popen ptrace_example anatomy


all: $(BINS)

rawhello: rawsyscall.S
	$(CC) $(CFLAGS) -nostdlib -o rawhello rawsyscall.S

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(BINS) 
	$(RM) -r *.dSYM

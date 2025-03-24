
CC=clang
CFLAGS=-Wall -g
BINS=sem mybank pthreadex pthreadex2 conditionex readwritelockex asyncio


all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ -pthread

asyncio: asyncio.c
	$(CC) $(CFLAGS) -o $@ $^ -pthread -lrt

mybank: interactivebank.c bank.o
	$(CC) $(CFLAGS) -o $@ interactivebank.c bank.o -pthread

clean:
	rm -rf $(BINS) *.o *.dSYM

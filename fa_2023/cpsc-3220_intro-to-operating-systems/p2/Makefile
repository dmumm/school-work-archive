CC=gcc
CFLAGS=-Wall -c

OBJ_FILES=mythread_common.o mythread_manage.o mythread_sync.o
BINS=libmythreads.a

all: $(BINS)

mythread_common.o: mythread_common.c mythread_common.h mythreads.h
	$(CC) $(CFLAGS) mythread_common.c

mythread_manage.o: mythread_manage.c mythreads.h mythread_common.h
	$(CC) $(CFLAGS) mythread_manage.c

mythread_sync.o: mythread_sync.c mythreads.h mythread_common.h
	$(CC) $(CFLAGS) mythread_sync.c

libmythreads.a: $(OBJ_FILES)
	ar rcs libmythreads.a $(OBJ_FILES)

clean:
	rm -f $(BINS) $(OBJ_FILES)

CC=cc
CFLAGS=$(OPT) -I../.. -Dunix -fPIC

UNZ_OBJS = miniunz.o unzip.o ioapi.o
ZIP_OBJS = minizip.o zip.o   ioapi.o

.c.o:
	$(CC) -c $(CFLAGS) $*.c

all: miniunz minizip

libminizip: unzip.o zip.o ioapi.o
	#$(CC) $(CFLAGS) -o libminizip.a unzip.o zip.o ioapi.o -lz 
	ar rcs libminizip.a unzip.o zip.o ioapi.o

miniunz:  $(UNZ_OBJS)
	$(CC) $(CFLAGS) -o $@ $(UNZ_OBJS) -L ../.. -lz

minizip:  $(ZIP_OBJS)
	$(CC) $(CFLAGS) -o $@ $(ZIP_OBJS) -L ../.. -lz

test:	miniunz minizip
	./minizip test readme.txt
	./miniunz -l test.zip
	mv readme.txt readme.old
	./miniunz test.zip

clean:
	/bin/rm -f *.o *~ minizip miniunz *.so *.a

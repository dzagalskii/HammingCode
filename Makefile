CC            = gcc
CFLAGS        = -Wall -std=c99
LDFLAGS       = -lm -s
PROGS         = hammingenc hammingdec

all: $(PROGS)

hammingenc: hammingenc.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

hammingdec: hammingdec.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean: $(PROGS)
	rm -f $^

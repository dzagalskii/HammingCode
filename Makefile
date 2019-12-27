CC            = gcc
CFLAGS        = -Wall -std=c99
LDFLAGS       = -s
SRCP          = src
PROGS         = hammingenc hammingdec

all: $(PROGS)

hammingenc: $(SRCP)/hammingenc.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

hammingdec: $(SRCP)/hammingdec.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean: $(PROGS)
	rm -f $^

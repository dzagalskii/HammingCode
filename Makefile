CC            = gcc
CFLAGS        = -Wall -std=c99
LDFLAGS       = -lm -s
PROGS         = hemingenc hemingdec

all: $(PROGS)

hemingenc: union_heming.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

hemingdec: union_deheming.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean: $(PROGS)
	rm -f $^

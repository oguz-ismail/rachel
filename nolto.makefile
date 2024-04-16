CFLAGS = -O3 -DNDEBUG

rachel: mono.o
	$(CC) $(LDFLAGS) -o $@ mono.o

mono.c: leaf.c main.c node.c node.h prune.c refine.c search.c stack.c
	awk -f mkmono.awk *.h *.c >mono.c

clean:
	rm -f rachel mono.c mono.o

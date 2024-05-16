CFLAGS = -O3 -DNDEBUG

rachel: merged.o
	$(CC) $(LDFLAGS) -o $@ merged.o

merged.c: leaf.c main.c node.c node.h out.c out.h prune.c refine.c search.c \
 stack.c
	awk -f merge.awk *.h *.c >merged.c

clean:
	rm -f rachel merged.c merged.o

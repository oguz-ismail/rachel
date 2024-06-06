CFLAGS = -O3 -DNDEBUG

bin = rachel
srcs = node.h out.h check.c leaf.c main.c node.c out.c prune.c refine.c \
	search.c stack.c

all: $(bin)

$(bin): merged.o
	$(CC) $(LDFLAGS) -o $@ merged.o

merged.c: $(srcs)
	awk -f scripts/merge.awk check.h leaf.h prune.h refine.h search.h \
		stack.h $(srcs) >merged.c

clean:
	rm -f $(bin) merged.c merged.o

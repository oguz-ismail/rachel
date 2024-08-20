CFLAGS = -O3 -DNDEBUG $(cflags)

bin = rachel
srcs = node.h os.h check.c leaf.c main.c node.c out.c prune.c refine.c \
	search.c stack.c

all: $(bin)

$(bin): merged.o
	$(CC) $(LDFLAGS) -o $@ merged.o

merged.c: $(srcs)
	awk -f merge.awk leaf.h stack.h $(srcs) >merged.c

clean:
	rm -f $(bin) merged.c merged.o

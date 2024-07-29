CFLAGS = -O3 -DNDEBUG $(xflags)

bin = rachel
srcs = node.h os.h check.c leaf.c main.c node.c out.c prune.c refine.c \
	search.c stack.c

all: $(bin)

$(bin): merged.o
	$(CC) $(LDFLAGS) -o $@ merged.o

merged.c: $(srcs)
	awk -f merge.awk check.h leaf.h prune.h refine.h search.h stack.h \
		$(srcs) >merged.c

clean:
	rm -f $(bin) merged.c merged.o

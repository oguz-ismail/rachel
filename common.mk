CPPFLAGS += -DNDEBUG
LDFLAGS += $(CFLAGS)

bin = rachel$(suffix)
objs = check.o leaf.o main.o node.o out.o prune.o refine.o search.o stack.o

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

all: $(bin)

$(bin): $(objs)
	$(CC) $(LDFLAGS) -o $@ $(objs)

check.o node.o prune.o refine.o search.o: node.h

main.o node.o: os.h

clean:
	rm -f $(bin) $(objs)

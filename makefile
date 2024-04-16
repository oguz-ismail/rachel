CPPFLAGS += -DNDEBUG
CFLAGS += -O3 -flto
LDFLAGS = $(CFLAGS)
OBJS = leaf.o main.o node.o prune.o refine.o search.o stack.o
BIN = rachel

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

node.o: node.h
prune.o: node.h
refine.o: node.h
search.o: node.h

clean:
	rm -f $(BIN) $(OBJS)

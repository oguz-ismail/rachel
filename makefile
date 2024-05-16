CPPFLAGS += -DNDEBUG
CFLAGS += -O3 -flto
LDFLAGS = $(CFLAGS)
OBJS = leaf.o main.o node.o out.o prune.o refine.o search.o stack.o
BIN = rachel

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

node.o prune.o refine.o search.o: node.h

main.o node.o search.o: out.h

clean:
	rm -f $(BIN) $(OBJS)

v0:
	git checkout ee727f
	$(MAKE)
	git switch -

CPPFLAGS += -DNDEBUG
LDFLAGS = $(CFLAGS)
OBJS = check.o leaf.o main.o node.o out.o prune.o refine.o search.o stack.o
BIN = rachel

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

check.o node.o prune.o refine.o search.o: node.h

main.o node.o search.o: out.h

clean:
	rm -f $(BIN) $(OBJS)

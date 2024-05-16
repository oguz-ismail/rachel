CFLAGS = /O2 /GL /DNDEBUG
LDFLAGS = /LTCG
OBJS = leaf.obj main.obj node.obj out.obj prune.obj refine.obj search.obj \
	stack.obj

rachel.exe: $(OBJS)
	link $(LDFLAGS) $(OBJS) /OUT:$@

node.obj prune.obj refine.obj search.obj: node.h

main.obj node.obj search.obj: out.h

clean:
	del /q rachel.exe $(OBJS)

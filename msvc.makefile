CFLAGS = /O2 /GL /DNDEBUG
LDFLAGS = /LTCG
OBJS = leaf.obj main.obj node.obj prune.obj refine.obj search.obj stack.obj

rachel.exe: $(OBJS)
	link $(LDFLAGS) $(OBJS) /OUT:$@

clean:
	del /q rachel.exe $(OBJS)

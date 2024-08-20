CFLAGS = /O2 /GL /DNDEBUG $(cflags)
LDFLAGS = /LTCG

bin = rachel.exe
objs = check.obj leaf.obj main.obj node.obj out.obj prune.obj refine.obj \
 search.obj stack.obj

all: $(bin)

$(bin): $(objs)
	link $(LDFLAGS) $(objs) /OUT:$@

node.obj prune.obj refine.obj search.obj: node.h

main.obj node.obj: os.h

clean:
	del /q $(bin) $(objs)

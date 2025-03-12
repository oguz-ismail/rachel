CFLAGS = /O2 /GL /DNDEBUG $(cflags)
LDFLAGS = /LTCG

bin = rachel.exe
objs = check.obj leaf.obj main.obj node.obj out.obj prune.obj refine.obj \
 search.obj stack.obj

!ifdef static
CFLAGS = $(CFLAGS) /GS- /Gs0x100000 /DSTATIC
LDFLAGS = $(LDFLAGS) $(ldflags) /nodefaultlib /stack:0x100000,0x100000 \
	/subsystem:console
ldflags = /dynamicbase:no
objs = $(objs) crtw32.obj
!endif

all: $(bin)

$(bin): $(objs)
	link $(LDFLAGS) $(objs) /OUT:$@ kernel32.lib

node.obj prune.obj refine.obj search.obj: node.h

main.obj node.obj: os.h

clean:
	del /q $(bin) $(objs)

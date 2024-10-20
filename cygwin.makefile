suffix = .exe

include makefile

static: CPPFLAGS += -DSTATIC
static: CFLAGS += -nostdlib -fno-builtin -mno-stack-arg-probe \
	-fno-unwind-tables -fno-asynchronous-unwind-tables
static: LDFLAGS += -Xlinker --stack=0x200000,0x200000 -Wl,--build-id=none
static: LDLIBS += -lkernel32
static clean: objs += crtw32.o

static: crtw32.o $(bin)

.PHONY: static

strip: static
	strip $(bin)
	ls -l $(bin)
	size $(bin)

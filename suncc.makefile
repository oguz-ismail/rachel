include common.mk

CFLAGS += $(cflags) -xipo -xvector=%none
cflags = -fast

static := CPPFLAGS += -DSTATIC
static := CFLAGS += -xbuiltin=%none
static clean := objs += crt.o
LD = /usr/ccs/bin/ld
ldflags = -dn -z nxstack
g = g

static: $$(objs)
	$(CC) $(CFLAGS) --help $(objs) >/dev/null 2>&1
	$(LD) $(ldflags) -o $(bin) $(objs)

strip: static
	$gobjcopy -S -j .bss -j .rodata1 -j .text $(bin) $(bin)
	ls -l $(bin)
	$gsize $(bin)

include common.mk

CFLAGS += $(cflags) -xipo -xvector=%none
cflags = -fast

static := CPPFLAGS += -DSTATIC
static := CFLAGS += -xbuiltin=%none
static clean := objs += crt.o
ldflags = -a -z nxstack
g = g

static: $$(objs)
	path=`dirname \`command -v $(CC)\``; \
	$$path/../lib/compilers/ipo \
		-phase2 -level=1 \
		-ubepath $$path/../lib/compilers/bin/ube \
		-fbepath $$path/fbe \
		-iroptpath $$path/../lib/compilers/bin/iropt \
		-ipo_ldarg_start $(objs) -ipo_ldarg_end
	ld $(ldflags) -o $(bin) $(objs)

strip: static
	$gobjcopy -S -j .bss -j .rodata1 -j .text $(bin) $(bin)
	ls -l $(bin)
	$gsize $(bin)

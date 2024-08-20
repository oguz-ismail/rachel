include common.mk

CPPFLAGS += -DSTATIC
CFLAGS += -O3 -fno-tree-vectorize -flto -nostdlib -fno-builtin \
	-fno-stack-protector -fno-pie -fno-unwind-tables \
	-fno-asynchronous-unwind-tables
LDFLAGS += -static -no-pie -Wl,-z,norelro -Wl,-z,noexecstack
objs += crt.o

.SUFFIXES: .S

.S.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

crt.o: crt.S

$(bin): crt.o

strip: $(bin)
	objcopy -S -j .rodata -j .bss -j .data.rel.ro -j .text \
		-j .note.ABI-tag -j .note.netbsd.ident -j .note.openbsd.ident \
		$(bin) $(bin)
	ls -l $(bin)
	size $(bin)

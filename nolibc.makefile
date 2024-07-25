include common.mk

CPPFLAGS += -DNOLIBC
CFLAGS += -O3 -fno-tree-vectorize -flto -nostdlib -fno-builtin \
	-fno-stack-protector -fno-pie -fno-unwind-tables \
	-fno-asynchronous-unwind-tables
LDFLAGS += -static -no-pie -Wl,-z,norelro
objs += libc.o

.SUFFIXES: .S

.S.o:
	$(CC) $(CFLAGS) -c -o $@ $<

libc.o: libc.S

$(bin): libc.o

strip: $(bin)
	objcopy -S -j .rodata -j .bss -j .data.rel.ro -j .text \
		-j .note.ABI-tag -j .note.netbsd.ident -j .note.openbsd.ident \
		$(bin) $(bin)
	ls -l $(bin)
	size $(bin)

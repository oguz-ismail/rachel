include common.mk

.SUFFIXES: .s

.s.o:
	$(CC) -c -o $@ $<

CPPFLAGS += -DNOLIBC
CFLAGS += -O3 -fno-tree-vectorize -flto -nostdlib -fno-builtin \
	-fno-stack-protector -fno-pie -fno-unwind-tables \
	-fno-asynchronous-unwind-tables
LDFLAGS += -static -no-pie -Wl,-z,norelro

target != scripts/target.sh $(CC)
libc = asm/$(target)/libc.o
objs += $(libc)

$(bin): $(libc)

$(libc): $(libc:.o=.s)

strip: $(bin)
	objcopy -S -j .rodata -j .bss -j .data.rel.ro -j .text \
		-j .note.ABI-tag -j .note.netbsd.ident -j .note.openbsd.ident \
		$(bin) $(bin)
	ls -l $(bin)
	size $(bin)

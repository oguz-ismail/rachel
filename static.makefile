include makefile

CPPFLAGS += -DSTATIC
CFLAGS += -nostdlib -fno-builtin -fno-stack-protector -fno-pie \
	-fno-unwind-tables -fno-asynchronous-unwind-tables \
	-fomit-frame-pointer
LDFLAGS += -static $(ldflags) -Wl,-z,norelro -Wl,-z,noexecstack
ldflags = -no-pie
objs += crt.o

.SUFFIXES: .S

.S.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

crt.o: crt.S

$(bin): crt.o

strip: $(bin)
	$gobjcopy -S -j .rodata -j .bss -j .data.rel.ro -j .text \
		-j .note.ABI-tag -j .note.netbsd.ident -j .note.openbsd.ident \
		-j .openbsd.syscalls $(bin) $(bin)
	ls -l $(bin)
	$gsize $(bin)

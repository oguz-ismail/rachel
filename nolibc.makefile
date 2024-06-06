include common.mk

.SUFFIXES: .s

.s.o:
	$(CC) -c -o $@ $<

CPPFLAGS += -DNOLIBC
CFLAGS += -O3 -flto -nostdlib -fno-builtin
LDFLAGS += -static

target != scripts/target.sh $(CC)
libc = asm/$(target)/libc.o
objs += $(libc)

$(bin): $(libc)

$(libc): $(libc:.o=.s)

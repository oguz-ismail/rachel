.global errno
.global _exit
.global _start
.global write

.bss

errno:
	.word

.text

_exit:
	mov w8, 1
	svc 0

_start:
	ldr w0, [sp]
	add x1, sp, 8
	bl main
	b _exit

write:
	mov w8, 4
	svc 0
	dsb nsh
	isb
	bcs .err
	ret
.err:
	adrp x1, errno
	str w0, [x1, :lo12:errno]
	mov w0, -1
	ret

.section .note.openbsd.ident, "a"
.long 8, 4, 1
.string "OpenBSD"
.long 0

.section .note.GNU-stack, ""

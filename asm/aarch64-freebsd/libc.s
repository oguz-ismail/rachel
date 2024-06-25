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
	add x1, x0, 8
	ldr w0, [x0]
	bl main
	b _exit

write:
	mov w8, 4
	svc 0
	bcs .err
	ret
.err:
	adrp x1, errno
	str w0, [x1, :lo12:errno]
	mov w0, -1
	ret

.section .note.ABI-tag, "a"
.long 8, 4, 1
.string "FreeBSD"
.long 0

.section .note.GNU-stack, ""

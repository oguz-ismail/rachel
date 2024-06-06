.global errno
.global _exit
.global _start
.global write

.data

errno:
	.word 0

.text

_exit:
	mov w8, #93
	svc #0

_start:
	ldr w0, [sp]
	add x1, sp, #8
	bl main
	bl _exit

write:
	mov w8, #64
	svc #0
	tbnz w0, #31, .err
	ret
.err:
	neg w0, w0
	adrp x1, errno
	str w0, [x1, #:lo12:errno]
	mov w0, #-1
	ret

.section .note.GNU-stack, ""

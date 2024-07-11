.include "asm/div.s"

.global errno
.global _exit
.global _start
.global write

.bss

errno:
	.word

.text

_exit:
	svc #0xa00001

_start:
	ldr r1, [r0]
	ldr r0, [r0, #4]
	bl main
	b _exit

write:
	svc #0xa00004
	bxcc lr

	movw r1, #:lower16:errno
	movt r1, #:upper16:errno
	str r0, [r1]
	mov r0, #-1
	bx lr

.section .note.netbsd.ident, "a"
.long 7, 4, 1
.string "NetBSD\0"
.long 0

.section .note.GNU-stack, ""

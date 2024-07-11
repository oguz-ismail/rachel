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
	mov r7, #1
	swi #0

_start:
	ldr r0, [sp]
	add r1, sp, #4
	bl main
	b _exit

write:
	mov ip, r7
	mov r7, #4
	swi #0
	mov r7, ip
	bxcc lr

	movw r1, #:lower16:errno
	movt r1, #:upper16:errno
	str r0, [r1]
	mov r0, #-1
	bx lr

.section .note.ABI-tag, "a"
.long 8, 4, 1
.string "FreeBSD"
.long 0

.section .note.GNU-stack, ""

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
	pop {r0}
	mov r1, sp
	bl main
	b _exit

write:
	push {r7}
	mov r7, #4
	swi #0
	pop {r7}
	cmn r0, #4096
	bxcc lr

	movw r1, #:lower16:errno
	movt r1, #:upper16:errno
	str r0, [r1]
	mov r0, #-1
	bx lr

.section .note.GNU-stack, ""

.type _exit, #function
.type write, #function
.type __aeabi_idiv, #function
.type __aeabi_idivmod, #function
.type __aeabi_uidiv, #function
.type __aeabi_uidivmod, #function

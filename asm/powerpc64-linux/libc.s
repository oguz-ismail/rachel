.abiversion 2

.global errno
.global _exit
.global _start
.global write

.bss

errno:
	.word

.text

_exit:
	li %r0, 1
	sc

_start:
	addis %r2, %r12, .TOC.-_start@ha
	addi %r2, %r2, .TOC.-_start@l
	lwz %r3, 0(%r1)
	addi %r4, %r1, 8
	stdu %r1, -16(%r1)
	bl main
	b _exit

write:
	li %r0, 4
	sc
	bso- .err
	blr
.err:
	lis %r4, errno@ha
	addi %r4, %r4, errno@l
	stw %r3, 0(%r4)
	li %r3, -1
	blr

.section .note.GNU-stack, ""

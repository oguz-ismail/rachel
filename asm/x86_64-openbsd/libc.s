.global errno
.global _exit
.global _start
.global write

.data

errno:
	.word 0

.text

_exit:
	mov $1, %eax
	syscall

_start:
	mov (%rsp), %rdi
	lea 8(%rsp), %rsi
	call main
	mov %eax, %edi
	call _exit

write:
	mov $4, %eax
	syscall
	jc .err
	ret
.err:
	mov %eax, errno(%rip)
	mov $-1, %eax
	ret

.section .note.openbsd.ident, "a"
.long 8, 4, 1
.string "OpenBSD"
.long 0

.section .note.GNU-stack, ""

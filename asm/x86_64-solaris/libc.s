.global errno
.global _exit
.global _start
.global write

.bss

errno:
	.word

.text

_exit:
	mov $1, %eax
	syscall

_start:
	mov (%rsp), %edi
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
	mov %eax, errno
	mov $-1, %eax
	ret

.section .note.GNU-stack, ""

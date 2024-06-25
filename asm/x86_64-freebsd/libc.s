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
	lea 8(%rdi), %rsi
	mov (%rdi), %edi
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

.section .note.ABI-tag, "a"
.long 8, 4, 1
.string "FreeBSD"
.long 0

.section .note.GNU-stack, ""

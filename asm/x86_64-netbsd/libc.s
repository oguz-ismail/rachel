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
	mov (%rbx), %rsi
	mov -8(%rsi), %edi
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

.section .note.netbsd.ident, "a"
.long 7, 4, 1
.string "NetBSD\0"
.long 0

.section .note.GNU-stack, ""

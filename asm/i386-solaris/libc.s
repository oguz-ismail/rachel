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
	int $145

_start:
	pop %eax
	push %esp
	push %eax
	call main
	push %eax
	call _exit

write:
	mov $4, %eax
	int $145
	jc .err
	ret
.err:
	mov %eax, errno
	mov $-1, %eax
	ret

.section .note.GNU-stack, ""

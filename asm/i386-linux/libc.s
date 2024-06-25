.global errno
.global _exit
.global _start
.global write

.bss

errno:
	.word

.text

_exit:
	mov 4(%esp), %ebx
	mov $1, %eax
	int $128

_start:
	pop %eax
	push %esp
	push %eax
	call main
	push %eax
	call _exit

write:
	push %ebx
	push %ecx
	push %edx
	mov 16(%esp), %ebx
	mov 20(%esp), %ecx
	mov 24(%esp), %edx
	mov $4, %eax
	int $128
	pop %edx
	pop %ecx
	pop %ebx
	test %eax, %eax
	js .err
	ret
.err:
	neg %eax
	mov %eax, errno
	mov $-1, %eax
	ret

.section .note.GNU-stack, ""

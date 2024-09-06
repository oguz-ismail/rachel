.global errno
.global _exit
.global _start
.global write

.bss

errno:
#if __SUNPRO_C
.size errno, 4
#else
	.word
#endif

.text

_exit:
#if __aarch64__ && (__FreeBSD__ || __OpenBSD__)
	mov w8, 1
	svc 0
#elif __aarch64__ && __linux__
	mov w8, 93
	svc 0
#elif __aarch64__ && __NetBSD__
	mov w17, 1
	svc 0
#elif __amd64__ && (__FreeBSD__ || __NetBSD__ || __OpenBSD__ || __sun__)
	mov $1, %eax
	syscall
#elif __amd64__ && __linux__
	mov $60, %eax
	syscall
#elif __arm__ && (__FreeBSD__ || __linux__)
	mov r7, #1
	swi #0
#elif __arm__ && __NetBSD__
	svc #0xa00001
#elif __i386__ && __linux__
	mov 4(%esp), %ebx
	mov $1, %eax
	int $128
#elif __i386__ && __sun__
	mov $1, %eax
	int $145
#elif __powerpc64__ && __linux__
	li %r0, 1
	sc
#elif __riscv && __linux__
	li a7, 93
	scall
#elif __s390x__ && __linux__
	lghi %r1, 1
	svc 0
#endif

_start:
#if __aarch64__ && __FreeBSD__
	add x1, x0, 8
	ldr w0, [x0]
	bl main
	b _exit
#elif __aarch64__ && (__linux__ || __NetBSD__ || __OpenBSD__)
	ldr w0, [sp]
	add x1, sp, 8
	bl main
	b _exit
#elif __amd64__ && __FreeBSD__
	lea 8(%rdi), %rsi
	mov (%rdi), %edi
	call main
	mov %eax, %edi
	call _exit
#elif __amd64__ && (__linux__ || __OpenBSD__ || __sun__)
	mov (%rsp), %edi
	lea 8(%rsp), %rsi
	call main
	mov %eax, %edi
	call _exit
#elif __amd64__ && __NetBSD__
	mov (%rbx), %rsi
	mov -8(%rsi), %edi
	call main
	mov %eax, %edi
	call _exit
#elif __arm__ && __FreeBSD__
	ldr r0, [sp]
	add r1, sp, #4
	bl main
	b _exit
#elif __arm__ && __linux__
	pop {r0}
	mov r1, sp
	bl main
	b _exit
#elif __arm__ && __NetBSD__
	ldr r1, [r0]
	ldr r0, [r0, #4]
	bl main
	b _exit
#elif __i386__ && (__linux__ || __sun__)
	pop %eax
	push %esp
	push %eax
	call main
	push %eax
	call _exit
#elif __powerpc64__ && __linux__
	addis %r2, %r12, .TOC.-_start@ha
	addi %r2, %r2, .TOC.-_start@l
	lwz %r3, 0(%r1)
	addi %r4, %r1, 8
	stdu %r1, -128(%r1)
	bl main
	b _exit
#elif __riscv && __riscv_xlen == 64 && __linux__
.option push
.option norelax
	la gp, __global_pointer$
.option pop
	ld a0, 0(sp)
	addi a1, sp, 8
	call main
	tail _exit
#elif __s390x__ && __linux__
	lg %r2, 0(%r15)
	la %r3, 8(%r15)
	aghi %r15, -176
	brasl %r14, main
	j _exit
#else
#error target not supported
#endif

write:
#if __aarch64__ && __FreeBSD__
	mov w8, 4
	svc 0
	bcs .Lerr
	ret
#elif __aarch64__ && __linux__
	mov w8, 64
	svc 0
	tbnz w0, 31, .Lerr
	ret
#elif __aarch64__ && __NetBSD__
	mov w17, 4
	svc 0
	bcs .Lerr
	ret
#elif __aarch64__ && __OpenBSD__
	mov w8, 4
	svc 0
	dsb nsh
	isb
	bcs .Lerr
	ret
#elif __amd64__ && (__FreeBSD__ || __NetBSD__ || __OpenBSD__ || __sun__)
	mov $4, %eax
	syscall
	jc .Lerr
	ret
#elif __amd64__ && __linux__
	mov $1, %eax
	syscall
	test %eax, %eax
	js .Lerr
	ret
#elif __arm__ && __FreeBSD__
	mov ip, r7
	mov r7, #4
	swi #0
	mov r7, ip
	bxcc lr
#elif __arm__ && __linux__
	push {r7}
	mov r7, #4
	swi #0
	pop {r7}
	cmp r0, #0
	bxcc lr
#elif __arm__ && __NetBSD__
	svc #0xa00004
	bxcc lr
#elif __i386__ && __linux__
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
	js .Lerr
	ret
#elif __i386__ && __sun__
	mov $4, %eax
	int $145
	jc .Lerr
	ret
#elif __powerpc64__ && __linux__
	li %r0, 4
	sc
	bso- .Lerr
	blr
#elif __riscv && __linux__
	li a7, 64
	scall
	bltz a0, .Lerr
	ret
#elif __s390x__ && __linux__
	lghi %r1, 4
	svc 0
	cgijl %r2, 0, .Lerr
	br %r14
#endif
.Lerr:
#if __aarch64__ && (__FreeBSD__ || __NetBSD__ || __OpenBSD__)
	adrp x1, errno
	str w0, [x1, :lo12:errno]
	mov w0, -1
	ret
#elif __aarch64__ && __linux__
	neg w0, w0
	adrp x1, errno
	str w0, [x1, :lo12:errno]
	mov w0, -1
	ret
#elif __amd64__ && (__FreeBSD__ || __NetBSD__ || __OpenBSD__ || __sun__)
	mov %eax, errno
	mov $-1, %eax
	ret
#elif __amd64__ && __linux__
	neg %eax
	mov %eax, errno
	mov $-1, %eax
	ret
#elif __arm__ && (__FreeBSD__ || __linux__ || __NetBSD__)
	movw r1, #:lower16:errno
	movt r1, #:upper16:errno
	str r0, [r1]
	mov r0, #-1
	bx lr
#elif __i386__ && __linux__
	neg %eax
	mov %eax, errno
	mov $-1, %eax
	ret
#elif __i386__ && __sun__
	mov %eax, errno
	mov $-1, %eax
	ret
#elif __powerpc64__ && __linux__
	lis %r4, errno@ha
	addi %r4, %r4, errno@l
	stw %r3, 0(%r4)
	li %r3, -1
	blr
#elif __riscv && __linux__
	neg a0, a0
	sw a0, errno, t1
	li a0, -1
	ret
#elif __s390x__ && __linux__
	lcr %r2, %r2
	strl %r2, errno
	lhi %r2, -1
	br %r14
#endif

#if __arm__
#include "div.asm"
#endif

#if __FreeBSD__
.section .note.ABI-tag, "a"
.long 8, 4, 1
.string "FreeBSD"
.long 0
#elif __NetBSD__
.section .note.netbsd.ident, "a"
.long 7, 4, 1
.string "NetBSD\0"
.long 0
#elif __OpenBSD__
.section .note.openbsd.ident, "a"
.long 8, 4, 1
.string "OpenBSD"
.long 0
#endif

#if __arm__ && __linux__
.type _exit, #function
.type write, #function
.type __aeabi_idiv, #function
.type __aeabi_idivmod, #function
.type __aeabi_uidiv, #function
.type __aeabi_uidivmod, #function
#endif

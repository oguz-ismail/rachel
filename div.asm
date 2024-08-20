/* Copyright (c) 2012 Jörg Mische <bobbl@gmx.de>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

.global __aeabi_idiv
.global __aeabi_idivmod
.global __aeabi_uidiv
.global __aeabi_uidivmod

.text

__aeabi_idiv:
	cmp r0, #0
	bge .Lnum_pos
	rsbs r0, r0, #0
	cmp r1, #0
	bge .Lneg_result
	rsbs r1, r1, #0
	b __aeabi_uidivmod
.Lnum_pos:
	cmp r1, #0
	bge __aeabi_uidivmod
	rsbs r1, r1, #0
.Lneg_result:
	push {lr}
	bl __aeabi_uidivmod
	rsbs r0, r0, #0
	pop {pc}

__aeabi_idivmod:
	cmp r0, #0
	bge .Lnum_pos_bis
	rsbs r0, r0, #0
	cmp r1, #0
	bge .Lneg_both
	rsbs r1, r1, #0
	push {lr}
	bl __aeabi_uidivmod
	rsbs r1, r1, #0
	pop {pc}
.Lneg_both:
	push {lr}
	bl __aeabi_uidivmod
	rsbs r0, r0, #0
	rsbs r1, r1, #0
	pop {pc}
.Lnum_pos_bis:
	cmp r1, #0
	bge __aeabi_uidivmod
	rsbs r1, r1, #0
	push {lr}
	bl __aeabi_uidivmod
	rsbs r0, r0, #0
	pop {pc}

__aeabi_uidiv:
__aeabi_uidivmod:
	cmp r1, #0
	bne .Lno_div0
	b __aeabi_idiv0
.Lno_div0:
	movs r2, #1
	movs r3, #0
	cmp r0, r1
	bls .Lsub_loop0
	adds r1, #0
	bmi .Lsub_loop0
.Ldenom_shift_loop:
	lsls r2, #1
	lsls r1, #1
	bmi .Lsub_loop0
	cmp r0, r1
	bhi .Ldenom_shift_loop
.Lsub_loop0:
	cmp r0, r1
	bcc .Ldont_sub0
	subs r0, r1
	orrs r3, r2
.Ldont_sub0:
	lsrs r1, #1
	lsrs r2, #1
	bne .Lsub_loop0
	mov r1, r0
	mov r0, r3
	bx lr
__aeabi_idiv0:
	bl __aeabi_idiv0

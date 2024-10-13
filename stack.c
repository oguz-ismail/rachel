/* Copyright 2024 Oğuz İsmail Uysal <oguzismailuysal@gmail.com>
 *
 * This file is part of Rachel.
 *
 * Rachel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include "stack.h"

static void *a[8];
static size_t n;

void
push(void *x) {
	assert(n < sizeof a/sizeof a[0]);
	a[n++] = x;
}

struct node *
pop(void) {
	assert(n > 0);
	return a[--n];
}

const struct node *
peek(void) {
	assert(n > 0);
	return a[n-1];
}

const struct node *
lift(void) {
	assert(n > 1);
	return a[n-2];
}

size_t
stack_size(void) {
	return n;
}

void
clear(void) {
	n = 0;
}

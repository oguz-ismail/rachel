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
#include <limits.h>
#include <stddef.h>
#include "leaf.h"
#include "stack.h"
#include "node.h"

static int
overflow(const struct node *v) {
	long x, y;

	if (v->type == LEAF)
		return 0;

	if (overflow(v->left) || overflow(v->right))
		return 1;

	x = v->LHS;
	y = v->RHS;
	assert(x > 0 && y > 0);

	switch (v->type) {
	case ADD:
		return x > LONG_MAX-y;
	case MUL:
		return x > LONG_MAX/y;
	default:
		return 0;
	}
}

static const struct node *
find(const struct node *v, long x) {
	const struct node *u;

	if (v->value == x)
		return v;

	if (v->type == LEAF)
		return NULL;

	u = find(v->left, x);
	if (u != NULL)
		return u;

	return find(v->right, x);
}

static int
sift(const struct node *v, const struct node *u) {
	const struct node *w;

	w = find(u, v->value);
	if (w != NULL && v->type > w->type)
		return 1;

	if (v->type == LEAF)
		return 0;

	return sift(v->left, u) || sift(v->right, u);
}

static int
duplication(const struct node *v) {
	if (v->type == LEAF)
		return 0;

	return sift(v->left, v->right) ||
		duplication(v->left) ||
		duplication(v->right);
}

static int
myopia(const struct node *v) {
	size_t i;
	const struct node *u;

	for (i = -1; (i = next(i)) != -1; ) {
		u = find(v, get(i));
		if (u != NULL && u->type != LEAF)
			return 1;
	}

	return 0;
}

static int
regression(const struct node *v) {
	if (v->type == LEAF)
		return 0;

	return find(v->left, v->value) != NULL ||
		find(v->right, v->value) != NULL ||
		regression(v->left) ||
		regression(v->right);
}

int
check(int aux) {
	const struct node *v;

	v = peek();
	if (overflow(v) || duplication(v))
		return 1;

	if (aux && (myopia(v) || regression(v)))
		return 1;

	return 0;
}

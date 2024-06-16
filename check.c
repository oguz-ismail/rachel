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

typedef const struct node *NODE;

static int
overflow(NODE v) {
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
	}

	return 0;
}

static int
find(long x, NODE v, NODE *p) {
	if (v->value == x) {
		if (p != NULL)
			*p = v;

		return 1;
	}

	if (v->type == LEAF)
		return 0;

	return find(x, v->left, p) || find(x, v->right, p);
}

static int
sift(NODE v, NODE u) {
	NODE w;

	if (find(v->value, u, &w) && v->type > w->type)
		return 1;

	if (v->type == LEAF)
		return 0;

	return sift(v->left, u) || sift(v->right, u);
}

static int
duplication(NODE v) {
	if (v->type == LEAF)
		return 0;

	return sift(v->left, v->right)
		|| duplication(v->left)
		|| duplication(v->right);
}

static int
shortsight(void) {
	NODE v, u;
	size_t i;

	v = peek();
	for (i = -1; (i = next(i)) != -1; ) {
		if (find(get(i), v, &u) && u->type != LEAF)
			return 1;
	}

	return 0;
}

static int
regression(NODE v) {
	if (v->type == LEAF)
		return 0;

	return find(v->value, v->left, NULL)
		|| find(v->value, v->right, NULL)
		|| regression(v->left)
		|| regression(v->right);
}

int
check(int aux) {
	NODE v;

	v = peek();
	if (overflow(v) || duplication(v))
		return 1;

	if (aux)
		return shortsight() || regression(v);

	return 0;
}

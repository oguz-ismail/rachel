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

#define COMMUT(t) ((t) & (ADD|MUL))

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

	return sift(v->right, u) || sift(v->left, u);
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

static int
branch(long x, int match, int follow, NODE v) {
	if (v->type & match)
		if (v->RHS == x || (COMMUT(v->type) && v->LHS == x))
			return 1;

	if (v->type == LEAF || !(v->type & follow))
		return 0;

	if (branch(x, match, follow, v->left))
		return 1;

	if (!COMMUT(v->type))
		match ^= follow;

	return branch(x, match, follow, v->right);
}

static int
half(long x, int match, int follow, NODE v) {
	if (x%2 == 0 && branch(x/2, match, follow, v))
		return 1;

	return branch(x, match, follow, v)
		|| branch(2*x, match, follow, v);
}

static int
detour(NODE v) {
	int (*fn)(long, int, int, NODE);
	int pair, t[2];

	if (v->type == LEAF)
		return 0;

	if (detour(v->left) || detour(v->right))
		return 1;

	fn = branch;
	switch (v->type) {
	case ADD:
	case SUB:
		fn = half;
		pair = ADD|SUB;
		break;
	case MUL:
	case DIV:
		pair = MUL|DIV;
		break;
	default:
		return 0;
	}

	t[0] = t[1] = pair^v->type;
	if (!COMMUT(v->type))
		t[1] = v->type;

	return fn(v->RHS, t[0], pair, v->left)
		|| fn(v->LHS, t[1], pair, v->right);
}

int
check(int aux) {
	NODE v;

	v = peek();
	if (overflow(v) || duplication(v))
		return 1;

	if (aux)
		return shortsight() || regression(v) || detour(v);

	return 0;
}

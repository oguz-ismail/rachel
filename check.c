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
	if (v->type == LEAF)
		return 0;

	if (overflow(v->left) || overflow(v->right))
		return 1;

	switch (v->type) {
	case ADD:
		return v->LHS > LONG_MAX - v->RHS;
	case MUL:
		return v->LHS > LONG_MAX / v->RHS;
	}

	return 0;
}

static NODE
find(long x, NODE v) {
	NODE u;

	if (v->value == x)
		return v;

	if (v->type == LEAF)
		return NULL;

	if ((u = find(x, v->left)))
		return u;

	return find(x, v->right);
}

static int
filter(NODE v, NODE u) {
	NODE w;

	if ((w = find(v->value, u)) && v->type > w->type)
		return 1;

	if (v->type == LEAF)
		return 0;

	return filter(v->right, u) || filter(v->left, u);
}

static int
duplicate(NODE v) {
	if (v->type == LEAF)
		return 0;

	return filter(v->left, v->right)
		|| duplicate(v->left)
		|| duplicate(v->right);
}

static int
verbose(void) {
	NODE v, u;
	size_t i;

	v = peek();
	for (i = -1; (i = next(i)) != -1; )
		if ((u = find(load(i), v)) && u->type != LEAF)
			return 1;

	return 0;
}

static int
circular(NODE v) {
	if (v->type == LEAF)
		return 0;

	return find(v->value, v->left)
		|| find(v->value, v->right)
		|| circular(v->left)
		|| circular(v->right);
}

static int
branch(long x, int half, int match, int follow, NODE v) {
	if (half) {
		if (branch(2*x, 0, match, follow, v))
			return 1;

		if (DIVS(x, 2) && branch(x/2, 0, match, follow, v))
			return 1;
	}

	if (v->type & match)
		if (v->RHS == x || (COMMUT(v->type) && v->LHS == x))
			return 1;

	if (v->type == LEAF || !(v->type & follow))
		return 0;

	if (branch(x, 0, match, follow, v->left))
		return 1;

	if (!COMMUT(v->type))
		match ^= follow;

	return branch(x, 0, match, follow, v->right);
}

static int
indirect(NODE v) {
	int add, pair, t;

	t = v->type;
	if (t == LEAF)
		return 0;

	if (indirect(v->left) || indirect(v->right))
		return 1;

	add = 0;
	switch (t) {
	case ADD:
	case SUB:
		add = 1;
		pair = ADD|SUB;
		break;
	case MUL:
	case DIV:
		pair = MUL|DIV;
		break;
	default:
		return 0;
	}

	if (branch(v->LHS, add, t, pair, v->right))
		return 1;

	if (!COMMUT(t))
		t ^= pair;

	return branch(v->RHS, add, t, pair, v->left);
}

int
check(int aux) {
	NODE v;

	v = peek();
	if (overflow(v) || duplicate(v))
		return 1;

	if (aux)
		return verbose() || circular(v) || indirect(v);

	return 0;
}

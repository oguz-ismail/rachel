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
#include "node.h"

static int
overflow(const struct node *v) {
	long x, y, max;

	if (v->type == LEAF)
		return 0;

	if (overflow(v->left) || overflow(v->right))
		return 1;

	x = v->left->value;
	y = v->right->value;
	assert(x > 0 && y > 0 && x > y);

	switch (v->type) {
	case ADD:
		max = LONG_MAX-y;
		break;
	case MUL:
		max = LONG_MAX/y;
		break;
	default:
		return 0;
	}

	return x > max;
}

static int
contains(const struct node *v, long x) {
	if (v->value == x)
		return 1;

	if (v->type == LEAF)
		return 0;

	return contains(v->left, x) || contains(v->right, x);
}

static int
regression(const struct node *v) {
	if (v->type == LEAF)
		return 0;

	return contains(v->left, v->value) ||
		contains(v->right, v->value) ||
		regression(v->left) ||
		regression(v->right);
}

int
check(const struct node *v) {
	return overflow(v) || regression(v);
}

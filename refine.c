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
#include "node.h"

static void
flip(struct node *v) {
	struct node *l;

	assert(v->type != LEAF);
	l = v->left;
	v->left = v->right;
	v->right = l;
}

static struct node *
rotate(struct node *v, struct node **e) {
	struct node *l;

	assert(v->type != LEAF);
	l = v->left;
	assert(l->type != LEAF);
	assert(*e == l->left || *e == l->right);
	l->value = v->value;
	v->left = *e;
	*e = v;

	return l;
}

static struct node *
invert(struct node *v, struct node **e, unsigned t) {
	struct node *u;

	u = rotate(v, e);
	u->type = t;
	flip(v);

	return u;
}

struct node *
refine(struct node *v) {
	struct node *l;
	long x, y;

	if (v->type == LEAF)
		return v;

	v->left = refine(v->left);
	v->right = refine(v->right);

	l = v->left;
	x = l->value;
	y = v->right->value;

	switch (v->type) {
	case ADD:
		if (x < y)
			flip(v);

		break;
	case SUB:
		if (l->type != ADD)
			break;

		if (l->right->value > y)
			l = rotate(v, &l->right);
		else if (l->right->value < y)
			l = invert(v, &l->right, SUB);
		else
			break;

		update(v);
		v = l;
		break;
	case MUL:
		if (x > y && (y%5 != 0 || x%5 == 0))
			flip(v);

		break;
	case DIV:
		if (l->type != MUL)
			break;

		if (l->left->value%y == 0)
			l = rotate(v, &l->left);
		else if (y%l->left->value == 0)
			flip(l = invert(v, &l->left, DIV));
		else if (l->right->value%y == 0)
			l = rotate(v, &l->right);
		else if (y%l->right->value == 0)
			l = invert(v, &l->right, DIV);
		else
			break;

		update(v);
		v = l;
		break;
	}

	return v;
}

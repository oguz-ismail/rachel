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
	struct node *u;

	assert(v->type != LEAF);
	u = v->left;
	v->left = v->right;
	v->right = u;
}

static struct node *
rotate(struct node *v, struct node **e) {
	struct node *l;

	assert(v->type != LEAF);
	l = v->left;
	assert(e == &l->left || e == &l->right);
	l->value = v->value;
	v->left = *e;
	*e = v;

	return l;
}

static struct node *
invert(struct node *v, struct node **e, int t) {
	struct node *u;

	u = rotate(v, e);
	u->type = t;
	flip(v);

	return u;
}

struct node *
reunite(struct node *v) {
	struct node *l, *u;

	switch (v->type) {
	case ADD:
	case MUL:
		l = v->left;
		if (l->type != v->type)
			break;

		if (l->LHS == v->RHS)
			u = rotate(v, &l->left);
		else if (l->RHS == v->RHS)
			u = rotate(v, &l->right);
		else
			break;

		update(v);
		return u;
	}

	return v;
}

struct node *
order(struct node *v) {
	struct node *l, *u;
	long x, y;

	l = v->left;
	x = v->LHS;
	y = v->RHS;

	switch (v->type) {
	case ADD:
		if (x < y)
			flip(v);

		break;
	case SUB:
		if (l->type != ADD)
			break;

		if (l->RHS > y)
			u = rotate(v, &l->right);
		else if (l->RHS < y)
			u = invert(v, &l->right, SUB);
		else
			break;

		update(v);
		return u;
	case MUL:
		if (x > y && (y%5 != 0 || x%5 == 0))
			flip(v);

		break;
	case DIV:
		if (l->type != MUL)
			break;

		if (l->LHS % y == 0)
			u = rotate(v, &l->left);
		else if (y % l->LHS == 0)
			flip(u = invert(v, &l->left, DIV));
		else if (l->RHS % y == 0)
			u = rotate(v, &l->right);
		else if (y % l->RHS == 0)
			u = invert(v, &l->right, DIV);
		else
			break;

		update(v);
		return u;
	}

	return v;
}

struct node *
refine(struct node *v) {
	if (v->type == LEAF)
		return v;

	v->left = refine(v->left);
	v->right = refine(v->right);

	return order(reunite(v));
}

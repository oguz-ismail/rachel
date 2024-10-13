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
#include "os.h"
#include "stack.h"
#include "node.h"

int
make(struct node *v, int t) {
	long x, y;

	x = lift()->value;
	y = peek()->value;
	assert(x > 0 && y > 0);
	switch (t) {
	case ADD:
		v->value = x+y;
		break;
	case SUB:
		if (x <= y)
			return 0;

		v->value = x-y;
		break;
	case MUL:
		v->value = x*y;
		break;
	case DIV:
		if (x < y || !DIVS(x, y))
			return 0;

		v->value = x/y;
		break;
	default:
		assert(0);
	}

	v->type = t;
	v->right = pop();
	v->left = pop();
	return 1;
}

void
update(struct node *v) {
	long x, y;

	if (v->type == LEAF)
		return;

	x = v->LHS;
	y = v->RHS;
	switch (v->type) {
	case ADD:
		v->value = x+y;
		break;
	case SUB:
		assert(x > y);
		v->value = x-y;
		break;
	case MUL:
		v->value = x*y;
		break;
	case DIV:
		assert(x >= y && DIVS(x, y));
		v->value = x/y;
		break;
	}
}

static const char *
symbol(int t) {
	switch (t) {
	case ADD:
		return " + ";
	case SUB:
		return " - ";
	case MUL:
		return " * ";
	case DIV:
		return " / ";
	}

	return "";
}

void
print(const struct node *v, int root) {
	if (v->type != LEAF) {
		print(v->left, 0);
		print(v->right, 0);
		PUTN(v->LHS);
		PUTS(symbol(v->type));
		PUTN(v->RHS);
	}
	else if (root) {
		PUTN(v->value);
	}
	else {
		return;
	}

	PUTS(" = ");
	PUTN(v->value);
	PUTS(EOL);
}

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
#include "node.h"
#include "prune.h"

unsigned
prune(unsigned ops) {
	const struct node *l, *r;
	int x, y;
	unsigned tl, tr;

	l = lift();
	r = peek();

	x = l->value;
	y = r->value;
	assert(x > 0 && y > 0);

	tl = l->type;
	tr = r->type;

	if (x < y || (x == y && tl == LEAF && tr != LEAF)) {
		ops &= ~(ADD|SUB|MUL|DIV);
		assert(!ops);
		return ops;
	}

	if (tr != LEAF) {
		switch (tr) {
		case ADD:
		case SUB:
			ops &= ~(ADD|SUB);
			break;
		case MUL:
		case DIV:
			ops &= ~(MUL|DIV);
			break;
		}
	}
	else if (tl != LEAF) {
		switch (tl) {
		case SUB:
			ops &= ~ADD;
			break;
		case DIV:
			ops &= ~MUL;
			break;
		}

		switch (tl) {
		case ADD:
		case SUB:
		case MUL:
		case DIV:
			if (l->right->value < y)
				ops &= ~tl;

			break;
		}
	}

	if (y == 1)
		ops &= ~(MUL|DIV);

	if (ops&SUB && x-y == y)
		ops &= ~SUB;

	if (ops&DIV && x/y == y)
		ops &= ~DIV;

	return ops;
}

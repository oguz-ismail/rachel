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
#include "leaf.h"
#include "stack.h"
#include "node.h"

int check(int);
int prune(int);
struct node *refine(struct node *);

int target;
static int oneoff;
static int skip;
static int found, leapt;

static int
search_depth(size_t d) {
	int try, t;
	struct node v, *answer;
	size_t i;

	if (stack_size() >= 2) {
		try = prune(LEAF-1);
		for (t = 1; t < LEAF; t <<= 1) {
			if (!(t & try) || !make(&v, t))
				continue;

			push(&v);
			if (search_depth(d))
				return 1;

			assert(peek() == &v);
			pop();
			assert(v.type != LEAF);
			push(v.left);
			push(v.right);
		}
	}

	if (d == 0) {
		if (stack_size() != 1 || peek()->value != target)
			return 0;

		found = 1;

		if (check(leapt))
			return 0;

		if (skip) {
			skip--;
			return 0;
		}

		answer = pop();
		if (oneoff)
			answer = refine(answer);

		print(answer, 1);
		return 1;
	}

	v.type = LEAF;
	for (i = -1; (i = next(i)) != -1; ) {
		v.value = use(i);
		push(&v);
		if (search_depth(d-1))
			return 1;

		pop();
		unuse(i);
	}

	return 0;
}

int
search(int mode) {
	size_t i, n;

	assert(target > 0);

	if (mode != -1)
		skip = mode;
	else
		oneoff = 1;

#ifdef REUSE
	leapt = found = 0;
	clear();
#endif
	n = leaf_count();
	for (i = 1; i <= n; i++) {
		if (search_depth(i))
			return 1;

		leapt = found;
	}

	return 0;
}

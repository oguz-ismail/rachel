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
#include <stddef.h>

static int a[8];
static size_t c[8];
#ifndef NDEBUG
static size_t used[8];
#endif
static size_t n, total;

void
put(int x) {
	size_t i, j;

	total++;

	j = n;
	for (i = n; i-- > 0; )
		if (x == a[i]) {
			c[i]++;
			return;
		}
		else if (x > a[i]) {
			j = i;
		}

	assert(n < sizeof a/sizeof a[0]);
	for (i = n; i > j; i--) {
		a[i] = a[i-1];
		c[i] = c[i-1];
	}

	a[j] = x;
	c[j] = 1;
	n++;
}

size_t
next(size_t i) {
	while (++i < n)
		if (c[i] != 0)
			return i;

	return -1;
}

int
use(size_t i) {
	assert(i < n);
	assert(c[i] > 0);
	c[i]--;
#ifndef NDEBUG
	used[i]++;
#endif
	return a[i];
}

void
unuse(size_t i) {
	assert(i < n);
	assert(used[i] > 0);
	c[i]++;
#ifndef NDEBUG
	used[i]--;
#endif
}

size_t
leaf_count(void) {
	return total;
}

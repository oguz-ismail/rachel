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
static size_t n, total;
static size_t avail[8], used[8];

void
save(int x) {
	size_t i, pos;

	total++;

	pos = n;
	for (i = n; i-- > 0; )
		if (x > a[i]) {
			pos = i;
		}
		else if (x == a[i]) {
			avail[i]++;
			return;
		}

	assert(n < sizeof a/sizeof a[0]);
	for (i = n; i > pos; i--) {
		a[i] = a[i-1];
		avail[i] = avail[i-1];
	}

	a[pos] = x;
	avail[pos] = 1;
	n++;
}

size_t
next(size_t i) {
	while (++i < n)
		if (avail[i] != 0)
			return i;

	return -1;
}

int
use(size_t i) {
	assert(i < n);
	assert(avail[i] > 0);
	avail[i]--;
#ifdef REUSE
	used[i]++;
#endif
	return a[i];
}

void
unuse(size_t i) {
	assert(i < n);
	avail[i]++;
	assert(used[i] > 0);
#ifdef REUSE
	used[i]--;
#endif
}

void
restore(void) {
	size_t i;
	for (i = 0; i < n; i++) {
		avail[i] += used[i];
		used[i] = 0;
	}
}

int
load(size_t i) {
	assert(i < n);
	return a[i];
}

size_t
leaf_count(void) {
	return total;
}

void
reset(void) {
	n = total = 0;
}

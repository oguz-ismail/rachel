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
#include <errno.h>
#include <stdlib.h>
#if _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "out.h"

static const int fd[2] = {1, 2};
static char buf[2][128];
static unsigned n[2];

void
print_string(int f, const char *p) {
	for (; *p; p++) {
		if (n[f] >= sizeof buf[0])
			flush(f);

		buf[f][n[f]++] = *p;

		if (*p == '\n')
			flush(f);
	}
}

void
print_number(int f, int x) {
	static char s[64];
	char *p;

	assert(x >= 0);

	p = &s[sizeof s-1];
	do {
		*--p = '0' + x%10;
		x /= 10;
	}
	while (x > 0);

	print_string(f, p);
}

void
flush(int f) {
	unsigned i;
	int k;

	for (i = 0; i < n[f]; i += k) {
		k = write(fd[f], &buf[f][i], n[f]-i);
		if (k == -1) {
			if (errno == EINTR) {
				k = 0;
				continue;
			}

			if (f != ERR)
				print_string(ERR, "write error\n");

			_exit(2);
		}
	}

	n[f] = 0;
}

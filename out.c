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

#ifndef GENERIC
#include <stddef.h>
#ifdef STATIC
#include "crt.h"
#else
#include <errno.h>
#include <stdlib.h>
#if _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#endif
#include "os.h"

static char a[128];
static size_t n;

static void
full_write(int fd, const char *buf, size_t count, int retry) {
	size_t i, ret;

	for (i = 0; i < count; ) {
		ret = write(fd, &buf[i], count-i);
		if (ret != -1) {
			i += ret;
			continue;
		}

		if (errno == EINTR && retry)
			continue;

		if (fd == 2)
			break;

		EPUTS("write error" EOL);
		EXIT(2);
	}
}

void
flush(void) {
	full_write(1, a, n, 1);
	n = 0;
}

static void
buffer(const char *p) {
	for (; *p; p++) {
		if (n >= sizeof a)
			flush();

		a[n++] = *p;

		if (*p == '\n')
			flush();
	}
}

void
print_string(int fd, const char *s) {
	size_t len;

	if (fd == 1) {
		buffer(s);
	}
	else {
		for (len = 0; s[len]; len++);
		full_write(fd, s, len, 0);
	}
}

void
print_number(int fd, long x) {
	static char buf[32];
	char *p;

	p = &buf[(sizeof buf)-1];
	do {
		*--p = '0' + x%10;
		x /= 10;
	}
	while (x > 0);

	print_string(fd, p);
}
#endif

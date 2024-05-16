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

#include <limits.h>
#if _WIN32
#include <stdlib.h>
#else
#include <unistd.h>
#endif
#include "leaf.h"
#include "out.h"
#include "search.h"

#define space(c) ((c) == ' ' || (c) == '\t')

static int
number(const char *s, int nonzero) {
	int x;
	const char *p, *start;
	int digit;

	p = s;
	for (; space(*p); p++);
	start = p;

	x = 0;
	for (; *p >= '0' && *p <= '9'; p++) {
		if (x > INT_MAX/10)
			goto err;

		x *= 10;
		digit = *p-'0';
		if (x > INT_MAX-digit)
			goto err;

		x += digit;
	}

	if (p == start || (nonzero && x == 0))
		goto err;

	for (; space(*p); p++);
	if (*p != '\0')
		goto err;

	return x;
err:
	errs("bad number: ");
	errs(s);
	errs("\n");
	_exit(2);
}

int
main(int argc, char *argv[]) {
	int skip;
	int i;
	const char *p;

	skip = -1;
	for (i = 1; i < argc; i++) {
		p = argv[i];

		if (*p++ != '-')
			break;

		if (*p == '-') {
			i++;
			break;
		}

		if (*p++ != 's' || (*p == '\0' && i >= argc-1)) {
			errs("Usage: "
				"rachel [-s skip_count] numbers target\n");
			return 2;
		}

		if (*p == '\0')
			p = argv[++i];

		skip = number(p, 0);
	}

	argc -= i;
	argv += i;

	if (argc < 2 || argc > 7) {
		errs("fewer/more operands than expected\n");
		return 2;
	}

	for (i = 0; i < argc-1; i++)
		put(number(argv[i], 1));

	if (!search(number(argv[i], 1), skip)) {
		errs("no answer\n");
		return 1;
	}

	return 0;
}

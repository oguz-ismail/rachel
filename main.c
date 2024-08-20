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
#include "leaf.h"
#include "os.h"

#define SPACE(c) ((c) == ' ' || (c) == '\t')
#define DIGIT(c) ((c) >= '0' && (c) <= '9')

extern int target;
int search(int);

static int
number(const char *s, int min) {
	int sum;
	const char *p;
	int digit;

	for (; SPACE(*s); s++);

	sum = 0;
	for (p = s; DIGIT(*p); p++) {
		if (sum > INT_MAX/10)
			goto err;

		sum *= 10;
		digit = *p-'0';
		if (sum > INT_MAX-digit)
			goto err;

		sum += digit;
	}

	if (p == s || sum < min)
		goto err;

	for (; SPACE(*p); p++);
	if (*p != '\0' && *p != '\n')
		goto err;

	return sum;
err:
	EPUTS("bad number: ");
	EPUTS(s);
	EPUTS("\n");
	EXIT(2);
}

int
main(int argc, char *argv[]) {
	int skip;
	int i;
	const char *p;

	skip = -1;
	for (i = 1; i < argc; i++) {
		p = argv[i];
		if (*p != '-')
			break;

		if (*++p == '-') {
			i++;
			break;
		}

		if (*p != 's' || (*++p == '\0' && i >= argc-1)) {
			EPUTS("Usage: ");
			EPUTS(argv[0]);
			EPUTS(" [-s skip_count] numbers target\n");
			EXIT(2);
		}

		if (*p == '\0')
			p = argv[++i];

		skip = number(p, 0);
	}

	argc -= i;
	argv += i;

	if (argc < 2 || argc > 7) {
		EPUTS("fewer/more operands than expected\n");
		return 2;
	}

	for (i = 0; i < argc-1; i++)
		save(number(argv[i], 1));

	target = number(argv[i], 1);
	if (!search(skip)) {
		EPUTS("no answer\n");
		return 1;
	}

#ifdef GENERIC
	fflush(NULL);
	if (ferror(stdout)) {
		EPUTS("write error\n");
		return 2;
	}
#endif

	return 0;
}

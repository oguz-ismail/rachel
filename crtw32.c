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

#include <windows.h>

#define DELIM(c) ((c) == ' ' || (c) == '\t')

int main(int, char **);

#undef errno
int errno;
static HANDLE a[3];

void
_exit(int status) {
	ExitProcess(status);
}

static int
unescape(const char **src, char *volatile *dst, int quot) {
	const char *p;
	int i, n;

	p = *src;
	if (*p == '\\') {
		while (*++p == '\\');
		if (*p != '"')
			return 0;

		n = p-*src;
		for (i = 0; i < n/2; i++)
			*(*dst)++ = '\\';

		if (n%2 != 0)
			*(*dst)++ = '"';
		else
			p--;
	}
	else if (quot && *p == '"') {
		for (; *(p+1) == '"'; p++);
		if (p == *src)
			return 0;

		n = p-*src + 2;
		for (i = 0; i < n/3; i++)
			*(*dst)++ = '"';

		if (n%3 != 1)
			p--;
	}
	else {
		return 0;
	}

	*src = p;
	return 1;
}

int
mainCRTStartup(void) {
	int argc;
	char buf[32767];
	char *argv[ARRAYSIZE(buf)/2];
	const char *p;
	char *q;
	int quot;

	p = GetCommandLineA();
	argv[0] = q = buf;
	quot = 0;
	for (; DELIM(*p); p++);
	for (; *p; p++)
		if (!quot && DELIM(*p))
			break;
		else if (*p == '"')
			quot = !quot;
		else
			*q++ = *p;

	*q++ = 0;

	for (argc = 1; ; argc++) {
		for (; DELIM(*p); p++);
		if (!*p)
			break;

		argv[argc] = q;
		quot = 0;
		for (; *p; p++)
			if (!quot && DELIM(*p))
				break;
			else if (unescape(&p, &q, quot))
				continue;
			else if (*p == '"')
				quot = !quot;
			else
				*q++ = *p;

		*q++ = 0;
	}

	argv[argc] = 0;
	a[0] = GetStdHandle(STD_INPUT_HANDLE);
	a[1] = GetStdHandle(STD_OUTPUT_HANDLE);
	a[2] = GetStdHandle(STD_ERROR_HANDLE);
	_exit(main(argc, argv));
}

int
write(int fd, const void *buf, unsigned count) {
	DWORD ret;

	if (!buf)
		errno = EINVAL;
	else if (!count)
		return 0;
	else if (fd < 0 || fd >= ARRAYSIZE(a))
		errno = EBADF;
	else if (!a[fd] || a[fd] == INVALID_HANDLE_VALUE)
		errno = EBADF;
	else if (!WriteFile(a[fd], buf, count, &ret, 0))
		switch (GetLastError()) {
		case ERROR_ACCESS_DENIED:
			errno = EBADF;
			break;
		case ERROR_DISK_FULL:
			errno = ENOSPC;
			break;
		case ERROR_NO_DATA:
			errno = EPIPE;
			break;
		default:
			errno = EINVAL;
		}
	else if (ret)
		return ret;
	else
		errno = ENOSPC;

	return -1;
}

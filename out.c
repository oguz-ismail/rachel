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
		if (k != -1)
			continue;

		if (errno == EINTR) {
			k = 0;
			continue;
		}

		if (f != ERR)
			print_string(ERR, "write error\n");

		_exit(2);
	}

	n[f] = 0;
}

#include <errno.h>
#include <stddef.h>

#undef errno
extern int errno;

_Noreturn void _exit(int);
int write(int, const void *, size_t);

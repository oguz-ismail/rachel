#include <errno.h>
#undef errno

extern int errno;

_Noreturn void _exit(int);
int write(int, void *, unsigned);

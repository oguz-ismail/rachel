#include <errno.h>

#undef errno
extern int errno;

#ifndef _MSC_VER
_Noreturn
#endif
void _exit(int);
int write(int, const void *, unsigned);

#ifndef GENERIC
#ifdef STATIC
#include "crt.h"
#else
#if _WIN32
#include <stdlib.h>
#else
#include <unistd.h>
#endif
#endif

#define PUTS(s)  dputs(s, 1)
#define PUTN(x)  dputs(string(x), 1)
#define EPUTS(s) dputs(s, 2)
#define EPUTN(x) dputs(string(x), 2)
#define EXIT(x)  _exit(x)

const char *string(long);
void dputs(const char *, int);
void flush(void);
#else
#include <stdio.h>
#include <stdlib.h>

#define PUTS(s)  fputs(s, stdout)
#define PUTN(x)  fprintf(stdout, "%ld", (long)(x))
#define EPUTS(s) fputs(s, stderr)
#define EPUTN(x) fprintf(stderr, "%ld", (long)(x))
#define EXIT(x)  exit(x)
#endif

#if _WIN32 && defined(STATIC)
#define EOL "\r\n"
#else
#define EOL "\n"
#endif

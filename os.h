#ifdef GENERIC
#include <stdio.h>
#include <stdlib.h>

#define PRTS(s) fputs(s, stdout)
#define PRTN(x) fprintf(stdout, "%ld", x)
#define EPRTS(s) fputs(s, stderr)
#define EPRTN(x) fprintf(stderr, "%ld", x)
#define EXIT(x) exit(x)
#else
#ifdef STATIC
#include "libc.h"
#elif _WIN32
#include <stdlib.h>
#else
#include <unistd.h>
#endif

#define PRTS(s) print_string(1, s)
#define PRTN(x) print_number(1, x)
#define EPRTS(s) print_string(2, s)
#define EPRTN(x) print_number(2, x)
#define EXIT(x) _exit(x)

void print_string(int, const char *);
void print_number(int, long);
void flush(void);
#endif

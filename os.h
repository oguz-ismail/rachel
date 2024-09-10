#ifndef GENERIC
#ifndef STATIC
#if _WIN32
#include <stdlib.h>
#else
#include <unistd.h>
#endif
#else
#include "crt.h"
#endif

#define PUTS(s)  print_string(1, s)
#define PUTN(x)  print_number(1, x)
#define EPUTS(s) print_string(2, s)
#define EPUTN(x) print_number(2, x)
#define EXIT(x)  _exit(x)

void print_string(int, const char *);
void print_number(int, long);
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

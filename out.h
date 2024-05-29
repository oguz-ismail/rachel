#define OUT 0
#define ERR 1

#define OUTS(s) print_string(OUT, s)
#define OUTN(x) print_number(OUT, x)
#define ERRS(s) print_string(ERR, s)
#define ERRN(x) print_number(ERR, x)

void print_string(int, const char *);
void print_number(int, long);
void flush(int);

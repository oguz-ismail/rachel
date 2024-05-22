#define OUT 0
#define ERR 1

#define outs(s) print_string(OUT, s)
#define outn(x) print_number(OUT, x)
#define errs(s) print_string(ERR, s)
#define errn(x) print_string(ERR, x)

void print_string(int, const char *);
void print_number(int, long);
void flush(int);

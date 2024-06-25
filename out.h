#define OUTS(s) print_string(1, s)
#define OUTN(x) print_number(1, x)
#define ERRS(s) print_string(2, s)
#define ERRN(x) print_number(2, x)

void print_string(int, const char *);
void print_number(int, long);
void flush(void);

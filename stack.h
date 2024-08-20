#include <stddef.h>

void push(void *);
struct node *pop(void);
const struct node *peek(void);
const struct node *lift(void);
size_t stack_size(void);

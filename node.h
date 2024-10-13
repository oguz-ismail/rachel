#define ADD  (1<<0)
#define SUB  (1<<1)
#define MUL  (1<<2)
#define DIV  (1<<3)
#define LEAF (1<<4)

#define LHS left->value
#define RHS right->value

#define DIVS(x, y) ((x)%(y) == 0)

struct node {
	long value;
	int type;
	struct node *left;
	struct node *right;
};

int make(struct node *, int);
void update(struct node *);
void print(const struct node *, int);

#define ADD (1U<<0)
#define SUB (1U<<1)
#define MUL (1U<<2)
#define DIV (1U<<3)
#define LEAF (1U<<4)

#define LHS left->value
#define RHS right->value

struct node {
	long value;
	unsigned type;
	struct node *left;
	struct node *right;
};

int make(struct node *, unsigned);
void update(struct node *);
void print(const struct node *, int);

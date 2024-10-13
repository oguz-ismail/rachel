#include <stddef.h>

void save(int);
size_t next(size_t);
int use(size_t);
void unuse(size_t);
void restore(void);
int load(size_t);
size_t leaf_count(void);
void reset(void);

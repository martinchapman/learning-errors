// determines if we are in membership or conjecture mode
#include "mode.c"

// cbmc stuff
#define bool _Bool
void assert(_Bool);
void __CPROVER_assume(_Bool);
void assume(_Bool assumption) { __CPROVER_assume(assumption); }
int nondet_int();
_Bool nondet_Bool();

#define word_length_bound 7
int _Learn_b[word_length_bound];  // an array that captures the actual path.
int _Learn_idx = 0;


#ifdef membership
#include "membership_query.c"
#else
#include "conjecture_query.c"
#endif





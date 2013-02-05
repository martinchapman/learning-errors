// determines if we are in membership or conjecture mode
#include "mode.c"

#define word_length_bound 7
int _Learn_b[word_length_bound];
int _Learn_idx = 0;

#define bool _Bool
void assert(_Bool);
void __CPROVER_assume(_Bool);
void assume(_Bool assumption) { __CPROVER_assume(assumption); }

int nondet_int();
#define _Learn_Pos _Learn_b[_Learn_idx++] = 1        
#define _Learn_Neg _Learn_b[_Learn_idx++] = 0




#ifdef membership
#include "membership_query.c"
#else
#include "conjecture_query.c"
#endif





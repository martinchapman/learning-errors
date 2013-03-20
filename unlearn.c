#define _Learn
#define _Learn_trap
#define _Learn_assert(x) assert(x) 


void assert(_Bool);
void __CPROVER_assume(_Bool);
//void assume(_Bool assumption) { __CPROVER_assume(assumption); }


int _Learn_check() {return 1;}
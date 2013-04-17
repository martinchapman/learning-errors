// cbmc stuff
#define bool _Bool
void assert(_Bool c){};
void __CPROVER_assume(_Bool c) {};
//void assume(_Bool assumption) { __CPROVER_assume(assumption); }
int nondet_int(){};
_Bool nondet_Bool(){};
long nondet_long(){};
void *nondet_pointer(){};

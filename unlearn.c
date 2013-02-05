#define _Learn_Pos 
#define _Learn_Neg 
#define _Learn_check(x) assert(x) 


void assert(_Bool);
void __CPROVER_assume(_Bool);
void assume(_Bool assumption) { __CPROVER_assume(assumption); }


int check() {return 1;}
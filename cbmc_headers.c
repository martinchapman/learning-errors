// cbmc stuff
#define bool _Bool
void assert(_Bool c);
void __CPROVER_assume(_Bool);
int nondet_int();
char nondet_char(); //!! added
_Bool nondet_Bool();

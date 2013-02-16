
#include "membership_data.c"
#define _Learn_Pos {if (_Learn_idx >= mq_length || _Learn_mq[_Learn_idx] != 1) assume(0); _Learn_b[_Learn_idx++] = 1;}   //take the positive branch; in while it corresponds to staying in the loop     
#define _Learn_Neg {if (_Learn_idx >= mq_length || _Learn_mq[_Learn_idx] != 0) assume(0); _Learn_b[_Learn_idx++] = 0;}   //take the negative branch; in while it corresponds to exiting the loop     

// we fail an assertion if the assertion condition is false, and the query corresponds exactly to the path that brought us here (note that it will not fail if the query is longer).
#define _Learn_assert(x) if (!x ) {_Learn_Pos; if (_Learn_idx == mq_length) assert(0); assume(0);}

#define _Learn_trap 
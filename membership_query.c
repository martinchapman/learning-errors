
#include "membership_data.c"
#define _Learn_Pos if (_Learn_idx >= mq_length || _Learn_mq[_Learn_idx] != 1) assume(0); _Learn_b[_Learn_idx++] = 1        
#define _Learn_Neg if (_Learn_idx >= mq_length || _Learn_mq[_Learn_idx] != 0) assume(0); _Learn_b[_Learn_idx++] = 1        

#define _Learn_assert(x) if (!x) {_Learn_Pos; assert(0);}

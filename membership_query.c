
#include "membership_data.c"
#define _Learn(x) {if (_Learn_idx >= mq_length || _Learn_mq[_Learn_idx] != x) assume(0); _Learn_b[_Learn_idx++] = x;}   

// we fail an assertion if the assertion condition is false, and the query corresponds exactly to the path that brought us here (note that it will not fail if the query is longer).
#define _Learn_assert(x) if (!x ) {  if ((_Learn_idx == mq_length - 1) &&  (_Learn_mq[mq_length-1] == AlphaBetSize - 1))          {_Learn_b[_Learn_idx++] = AlphaBetSize - 1;   assert(0);}} assume(0);

//#define _Learn_assert(x) if (!x ) {  if ((_Learn_idx == mq_length - 1){{if (_Learn_mq[mq_length-1] != AlphaBetSize - 1) assume(0); _Learn_b[_Learn_idx++] = AlphaBetSize - 1;}; assert(0);}} assume(0);
//#define   _Learn_assert(x) if (!x ) {  if ((_Learn_idx == mq_length - 1)  {_Learn(AlphaBetSize - 1); assert(0);}} assume(0);




#define _Learn_trap 

// we fail an assertion if the assertion condition is false, and the query corresponds exactly to the path that brought us here (note that it will not fail if the query is longer).
#define _Learn_assert(x) membership_Assert(x);

#define _Learn_trap 

void membership_Assert (bool x);
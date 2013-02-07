#define _Learn_Pos _Learn_b[_Learn_idx++] = 1        
#define _Learn_Neg _Learn_b[_Learn_idx++] = 0

#define _Learn_assert(x) if (x) _Learn_Neg; else _Learn_Pos; check_conjecture(x);
#include "conjecture_data.c"

void check_conjecture(bool assert_condition) {
	char state = 0;
	int sim_idx = 0;
	for (int i = 0; i < _Learn_idx; ++i) // we need to unroll at least to _Learn_idx
		state = A[state][_Learn_b[sim_idx++]];
	if (assert_condition)
	{
		if (accept[state]) assert(0); // negative feedback: trace accepted, although it satisfies assertion.
	}
	else
	{
		if (!accept[state]) assert(0); // positive feedback: trace rejected, although it does not satisfy assertion.
	}	
}
	
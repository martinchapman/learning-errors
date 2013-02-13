#define _Learn_Pos _Learn_b[_Learn_idx++] = 1        
#define _Learn_Neg _Learn_b[_Learn_idx++] = 0

// Leran_trap: the idea is to fail paths that got here and correspond to an accepting state. 
// 1st line below: paths that go through the assertion and do not invoke the assertion, still get here. They will skip the for loop below and jump to check_conjecture(1), which will wrongly fail them.
// 2nd line below: nondet completion of the path.
// 3rd line below: we invoke it with assert_condition = 1 because we want the condition  "if (accept[state]) assert(0)" in _Learn_assert to be checked.
#define _Learn_trap if (_Learn_idx  == word_length_bound) assume(0);  \
					for (;_Learn_idx < word_length_bound; ++_Learn_idx ) {_Learn_b[_Learn_idx ] =  nondet_int(); assume(_Learn_b[_Learn_idx ] == 0 || _Learn_b[_Learn_idx ] == 1);} \
					check_conjecture(1) 


#define _Learn_assert(x) if (x) _Learn_Neg; else _Learn_Pos; check_conjecture(x);
#include "conjecture_data.c"

void check_conjecture(bool assert_condition) {
	char state = 0;
	int sim_idx = 0;
	for (int i = 0; i < _Learn_idx; ++i) // we need to unroll at least to _Learn_idx
		state = A[state][_Learn_b[sim_idx++]];
	if (assert_condition)
	{
		if (accept[state]) assert(0); // 1) negative feedback: trace accepted, although it satisfies assertion.  2) This line is also invoked because of _Learn_trap. It corresponds to non-existing paths that are still accepted by the candidate.
	}
	else
	{
		if (!accept[state]) assert(0); // positive feedback: trace rejected, although it does not satisfy assertion.
	}	
}
	
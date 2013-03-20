#define _Learn(x) {_Learn_b[_Learn_idx++] = x;}

int _Learn_ce_length;

// Learn_trap: every suffix beyond the end of the program is supposed to be rejected. Here we complete it with a nondeterministic suffix (up to length word_length_bound) and fail an assertion if it leads to an aacepting state.
// 1st line below: nondet completion of the path.
// 2nd line below: we invoke check_conjecture at each step with assert_condition = 1 because we want the condition  "if (accept[state]) assert(0)" in _Learn_assert to be checked.
#define _Learn_trap for (;_Learn_idx < word_length_bound; _Learn_idx ) {_Learn_b[_Learn_idx] =  nondet_int(); \
	__CPROVER_assume(_Learn_b[_Learn_idx ] >= 0 && _Learn_b[_Learn_idx ] < AlphaBetSize); _Learn_idx++; check_conjecture(1); } 
					

// the introduction of res below is because 'x' might be a function with side effects -- we do not want to call it twice.
#define _Learn_assert(x) {bool res = x; if (!res) {_Learn(AlphaBetSize - 1);} check_conjecture(res);}
#include "conjecture_data.c"

// called from _Learn_assert and from _Learn_trap. 
// From _Learn_assert : causes an assertion fail if the path so far (_Learn_b up to index _Learn_idx) disagrees with the automaton, i.e., the automaton says 'accept' although the assertion holds (negative feedback)
// or the automaon is not in an accepting state although the assertion fails (positive feedback). 
// From _Learn_trap: see documentation there. 
void check_conjecture(bool assert_condition) {  
	char state = 0;
	int sim_idx = 0;
	for (int i = 0; i < _Learn_idx; ++i) // we need to unroll at least to _Learn_idx
		state = A[state][_Learn_b[sim_idx++]];
	if (assert_condition)
	{
		if (accept[state]) {
			_Learn_ce_length = _Learn_idx;
			assert(0); // 1) negative feedback: trace accepted, although it satisfies assertion.  2) This line is also invoked because of _Learn_trap. It corresponds to non-existing paths that are still accepted by the candidate.
		}
	}
	else
	{
		if (!accept[state]) {
			_Learn_ce_length = _Learn_idx;
			assert(0); // positive feedback: trace rejected, although it does not satisfy assertion.
		}
	}
	if (_Learn_idx  == word_length_bound) __CPROVER_assume(0); // paths that go through the assertion and do not invoke the assertion, still get here. They will skip the for loop below and jump to check_conjecture(1), which will wrongly fail them.
}
	
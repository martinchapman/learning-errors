#include "learn.h"
#include "conjecture_data.h"
#include "membership_data.h"

//extern int _Learn_b[word_length_bound];  
//extern int _Learn_idx;
//extern int _Learn_ce_length;

int _Learn_b[word_length_bound];  // an array that captures the actual path.
int _Learn_idx = 0;
int _Learn_ce_length;

#ifdef membership				// defines the mode: membership queries or checking the conjecture
#include "membership_data.c"
#include "membership_query.c"
#else
#include "conjecture_data.c"
#include "conjecture_query.c"
#endif



void _Learn_branch(int _Learn_letter) { _Learn(_Learn_letter);};
void _Learn_function_enter(int _Learn_letter) { _Learn(_Learn_letter);};

#ifdef conjecture
void check_conjecture(bool assert_condition) {  
	char state = 0;
	int sim_idx = 0;
	for (int i = 0; i < _Learn_idx; ++i) // we need to unroll at least to _Learn_idx
		state = A[state][_Learn_b[sim_idx++]];
	if (assert_condition)
	{
		if (accept[state]) {
			_Learn_ce_length = _Learn_idx;
			assert(0); // negative feedback: trace accepted, although it satisfies assertion.  
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
	
// called from _Learn_trap. At the trap we are only interested in negative feedbacks (everything that gets here is not in the language).
void check_conjecture_at_trap() {  
	char state = 0;
	int sim_idx = 0;
	for (int i = 0; i < _Learn_idx; ++i) // we need to unroll at least to _Learn_idx
		state = A[state][_Learn_b[sim_idx++]];
	if (accept[state]) {
		// positive_queries_filter filters out (via assume(0)) paths that are in the language (we know that because a previous mem. query proved so). This prevents nondeterminism, i.e., earlier we said it is in the language, and now we return it as a negative feedback.
		// note that this nondeterminisims is artificial, due to the trap, e.g., a path 0-1-1-2 breaks the assertion, but there is another path that doesn;t go via any of these locations and simply reaches the trap.
#include "positive_queries_filter.c"
		_Learn_ce_length = _Learn_idx;
		assert(0); // negative feedback related to non-existing paths that are still accepted by the candidate. 
	}	
}

void Learn_Assert(bool x) { 
	bool res = x; if (!res) {_Learn(AlphaBetSize - 1);} check_conjecture(res);
}

// Learn_trap: every suffix beyond the end of the program is supposed to be rejected. Here we complete it with a nondeterministic suffix (up to length word_length_bound) and fail an assertion if it leads to an aacepting state.
// 1st line below: nondet completion of the path.
// 2nd line below: we invoke check_conjecture_at_trap at each step.
void Learn_trap() {
	for (;_Learn_idx < word_length_bound; ) {
		_Learn_b[_Learn_idx] =  nondet_int(); 
		__CPROVER_assume(_Learn_b[_Learn_idx ] >= 0 && _Learn_b[_Learn_idx ] < AlphaBetSize ); 
		_Learn_idx++; check_conjecture_at_trap(); 
	} 
}


#else
void membership_Learn(int x) { 
	if (_Learn_idx >= mq_length || _Learn_mq[_Learn_idx] != x) __CPROVER_assume(0); 
	_Learn_b[_Learn_idx++] = x;
}

void Learn_Assert(bool x) { 
	if (!x ) {  if ((_Learn_idx == mq_length - 1) &&  (_Learn_mq[mq_length-1] == AlphaBetSize - 1)) {_Learn_b[_Learn_idx++] = AlphaBetSize - 1;   assert(0);}} __CPROVER_assume(0);
}
void Learn_trap() {}
#endif


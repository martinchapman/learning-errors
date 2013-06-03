#include "learn.h"
#include "conjecture_data.h"
//#include "membership_data.h"  // included from membeship_data.c anyway

#define assert_letter AlphaBetSize - 1

int _Learn_b[word_length_bound];  // an array that captures the actual path.
int _Learn_idx = 0;
int _Learn_ce_length;

#ifdef membership				// defines the mode: membership queries or checking the conjecture
#include "membership_data.c"
#else
#include "conjecture_data.c"
#endif



void _Learn_branch(int _Learn_letter) { _Learn(_Learn_letter);};
void _Learn_function_enter(int _Learn_letter) { _Learn(_Learn_letter);};


void Assert(bool x) { // we need to wrap 'assert' because goto-instrument --show-call-sequences does not refer to leaf functions. So we get 'Assert' in the report and replace it later with 'assert'.
	assert(x);
}

#ifdef conjecture
void check_conjecture(bool assert_condition) {  
	char state = 0;
	int sim_idx = 0;	
	for (int i = 0; i < _Learn_idx; ++i) // we need to unroll at least to _Learn_idx
		state = A[state][_Learn_b[sim_idx++]];
	if (assert_condition == accept[state]) { // Both true: negative feedback. Both false: positive feedback.
		_Learn_ce_length = _Learn_idx;		
		Assert(0); // !! can change to assert(0, assert_condition). Then from the ce we will know if it is a positive or negative feedback, which will save us checking membership of the first query.
	}	
	
	if (_Learn_idx  == word_length_bound) __CPROVER_assume(0); // it is possible that we continue beyond word_length_bound (e.g. cbmc has nested loops, hence the internal loop with the assert will be hit more than word_length_bound times). With this line, we truncate these paths. Without it, we may improve the automaton beyond the word_length. But we cannot activate it as long as we use arrays with size word_length_bound (we should use a bigger number / infinite arrays).
}
	
// called from _Learn_trap. At the trap we are only interested in negative feedbacks (everything that gets here is not in the language).
void check_conjecture_at_trap() {  
	char state = 0;
	int sim_idx = 0;
	for (int i = 0; i < _Learn_idx; ++i) // we need to unroll at least to _Learn_idx
		state = A[state][_Learn_b[sim_idx++]];
	if (accept[state]) {
		// positive_queries_filter filters out (via assume(0)) paths that are in the language (we know that because a previous mem. query proved so). This prevents nondeterminism, i.e., earlier we said it is in the language, and now we return it as a negative feedback.
		// note that this non-determinisms is artificial, due to the trap, e.g., a path 0-1-1-2 breaks the assertion, but there is another path that doesn't go via any of these locations and simply reaches the trap.
#include "positive_queries_filter.c"
		_Learn_ce_length = _Learn_idx;
		Assert(0); // negative feedback related to non-existing paths that are still accepted by the candidate. 
	}	
}

void Learn_Assert(bool assert_condition) { 	 
	if (!assert_condition) {_Learn(assert_letter);} // we call _Learn only when !res because our queries never include 'assert' more than once, hence we do not count asserts that pass.
	check_conjecture(assert_condition); 
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
	_Learn_idx++;
}

void Learn_Assert(bool x) { 
	if (!x ) {  
		if ((_Learn_idx == mq_length - 1) &&  (_Learn_mq[mq_length-1] == assert_letter)) { // since we screen out words that do not end with assertion, the 2nd check is redundant. 
			_Learn_idx++;
			Assert(0);
		} 
		__CPROVER_assume(0);
	} 
}
void Learn_trap() {}
#endif


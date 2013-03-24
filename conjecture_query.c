


void Learn_trap();

#define _Learn_trap Learn_trap(); 
					

// the introduction of res below is because 'x' might be a function with side effects -- we do not want to call it twice.
#define _Learn_assert(x) conjecture_Assert(x); 


// called from _Learn_assert . 
// From _Learn_assert : causes an assertion fail if the path so far (_Learn_b up to index _Learn_idx) disagrees with the automaton, i.e., the automaton says 'accept' although the assertion holds (negative feedback)
// or the automaon is not in an accepting state although the assertion fails (positive feedback). 
void check_conjecture(bool assert_condition) ;
// called from _Learn_trap. At the trap we are only interested in negative feedbacks (everything that gets here is not in the language).
void check_conjecture_at_trap();
void conjecture_Assert(bool x) ;
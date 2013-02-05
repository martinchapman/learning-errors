#ifdef word_length_bound
#undef word_length_bound
#endif
#define _Learn_check(x) if (!x) {_Learn_Pos; assume(check_membership()); assert(0);}


#include "membership_data.c"


int check_membership() {
	if (_Learn_idx > word_length_bound) return 0;
	for (int i = 0; i < _Learn_idx ; ++i) // we check up to _Learn_idx and not up to mqsize, because we assume that the accepting state (the "assert false" state) has a self loop. Hence  
		if (_Learn_b[i] != _Learn_mq[i]) return 0;
	return 1;
}
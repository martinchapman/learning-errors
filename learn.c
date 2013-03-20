// determines if we are in membership or conjecture mode
#include <string.h>
#include "mode.c"
#include "word_length.c"
#include "cbmc_headers.c"

int _Learn_b[word_length_bound];  // an array that captures the actual path.
int _Learn_idx = 0;


#ifdef membership				// defines the mode: membership queries or checking the conjecture
#include "membership_query.c"
#else
#include "conjecture_query.c"
#endif

// for automatic instrumentation
void _Learn_branch(const char *st) {
	if (!strcmp(st, "taken")) {_Learn(1);}
	else _Learn(0);
}

void _Learn_function_enter(const char *st) {
#include "FuncNameToNum.c"
}





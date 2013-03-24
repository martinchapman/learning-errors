// determines if we are in membership or conjecture mode
#include <string.h>

#include "learn.h"

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

// for automatic instrumentation

// do not change anything in the following 2 lines -- not even spaces. It is replaced later with sed after goto-instrument, with _Learn_function_enter(int ...)
// the sed lines are generated in onlince.cpp, into a batch file called convert.bat.
// check if still necessary given that it is now defined in learn_code.c
void _Learn_branch(const char *);
void _Learn_function_enter(const char *);





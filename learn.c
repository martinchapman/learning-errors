#ifndef __LEARN_INCLUDED__
#define __LEARN_INCLUDED__
#include "cbmc_headers.c"

//#define _Learn_trap Learn_trap(); 

#define _Learn_assert(x) Learn_Assert(x); 
void _Learn(int);

// for automatic instrumentation

// do not change anything in the following 2 lines -- not even spaces. It is replaced later with sed after goto-instrument, with _Learn_function_enter(int ...)
// the sed lines are generated in onlince.cpp, into a batch file called convert.bat.
// check if still necessary given that it is now defined in learn_code.c
//void _Learn_branch(const char *);
//void _Learn_function_enter(const char *);
void Learn_trap();
void Learn_Assert(bool x); 
#endif


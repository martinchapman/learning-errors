#ifndef __LEARN_H
#define __LEARN_H

#include "mode.c"
#include "word_length.c"
#include "cbmc_headers.c"


#ifdef membership				// defines the mode: membership queries or checking the conjecture
void membership_Learn(int x);
#define _Learn(x) membership_Learn(x); // we put it in a function in learn_code, so --branch instrumentation won't instrument it. 
#else
#define _Learn(x) {_Learn_b[_Learn_idx++] = x;}
#endif



#endif
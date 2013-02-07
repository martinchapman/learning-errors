#include "learn.c"

void f(int x) {
	while (x < 10)
	{		
		_Learn_Pos;
		x = nondet_int();
	}
	_Learn_Neg;
	_Learn_assert(x <= 20); // was assert(x <= 20);	
	
}



void main() {
  int x = nondet_int();
	f(x);
}
#include "learn.c"

void f(int x) {
	while (x < 10)
	{		
		_Learn(1);
		x = nondet_int();
	}
	_Learn(0);
	_Learn_assert(x <= 20); // was assert(x <= 20);	
	
}



void main() {
  int x = nondet_int();
	f(x);
  _Learn_trap;
}
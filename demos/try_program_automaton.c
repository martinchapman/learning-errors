 
int h(int x){
	return (x-1);
}

int r() {
	return 5;
}

int g(int x) {
	if (x) x = r();
	return x;
}

void f(int x) {
	x = g(x);
	if (x > 0)
	{
	// _Learn_assert(x >= 20); 
		x = h(x);
	return;
	}
	
}



void main() {
  
	int x = nondet_int();
	
	f(x);	
  
	_Learn_assert(0); 
}
 

int g(int x) {
	return x;
}

void f(int x) {
	if (x > 0)
	{
	_Learn_assert(x >= 20); // was assert(x <= 20);	
	return;
	}
	
}



void main() {
  
	int x = nondet_int();
	
	for(int i=0; i <x; i++){
	//	x++;
		if (x < 5) g(x);
	}
	f(x);	
  
}
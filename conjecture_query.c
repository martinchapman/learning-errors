#define _Learn_Pos _Learn_b[_Learn_idx++] = 1        
#define _Learn_Neg _Learn_b[_Learn_idx++] = 0

#define _Learn_check(x) if (x) _Learn_Neg; else _Learn_Pos; check_conjecture(x);


void check_conjecture(bool assert_condition) {
	char state = 0;
	int sim_idx = 0;
	for (int i = 0; i < _Learn_idx; ++i) {
		switch(state) {
		case 0: if (_Learn_b[sim_idx] == 0) state = 1; else state = 0; break;			
		case 1: if (_Learn_b[sim_idx] == 0) state = 0; else state = 2; break;		
			
		case 2: break;
		}
		sim_idx++;
	}

	if (assert_condition)
	{
		if (state == 2) assert(0); // negative feedback: trace accepted, although it satisfies assertion.
	}
	else
	{
		if (state != 2) assert(0); // positive feedback: trace rejected, although it does not satisfy assertion.
	}	
}


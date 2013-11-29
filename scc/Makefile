SRC = automaton_domination dominators

CLAGS = -Wall

dominators: $(SRC:%=%.o)
	g++ $^ -o $@ $(CFLAGS)
	cp dominators ../

%.o: %.c
	g++ $< -c -o $@ $(CFLAGS)
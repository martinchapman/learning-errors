SRC = automaton_domination dominators

CFLAGS = -I/sw/opt/boost-1_55/include -Wall

all: dominators dfs

dominators: $(SRC:%=%.o)
	g++ $^ -o $@ $(CFLAGS)
	cp dominators ../

dfs: $(SRC:%=%.o)
	g++ $^ -o $@ $(CFLAGS)
	cp dfs ../

%.o: %.cpp
	g++ $< -c -o $@ $(CFLAGS)

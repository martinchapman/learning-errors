
#include <fstream>

#include "../file_names.h"
#include "dominators.hpp"

using namespace std;
using namespace boost;


 // The automaton in automaton.data is specified as follows: 
// first line: <# vertices> < sizes of alphabet>
// second line: vector of 0 / 1 of size equal to the # of vertices. 1 indicates it is an accepting state. 
// edges ... 
void populate(dominators::myGraph_t *myGraph, int *target){
	typedef dominators::myGraph_t::edge edge;
	
	int i1, i2;
	FILE *in = fopen(AUTOMATON, "r");

	fscanf(in, "%d %d", &(myGraph->numOfVertices), &i1); // i1 will not be used (it is the size of the alphabet, which we do not use).

	for (i2 = 0 ; i2 < myGraph->numOfVertices; ++i2) // finding accepting state
	{
		fscanf(in, "%d", &i1);
		if (i1) *target = i2;   // so we're getting the last accepting state (normally there should only be 1)		  	 	  
	}

	while (!feof(in)) 
	{
		if (fscanf(in, "%d %d", &i1, &i2) != 2) continue;
		myGraph->edges.push_back(edge(i1, i2));
	}
}



int main()
{
	dominators dom;
	dominators::myGraph_t myGraph;
	int target = 0;
	
	populate(&myGraph, &target);	
	
	dom.find_dominators(myGraph, 0);
	
	if (target) dom.print(target);

/*	if (dom.isDom(0,3)) printf("0,3");
	if (dom.isDom(1,3)) printf("1,3");
	if (dom.isDom(3,0)) printf("3,0"); */
	
	return 0;
}

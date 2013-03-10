
// input: automaton (from automaton.data)
// output: doomed states, i.e., states that can only reach the accepting state.
// 1) reverses edges and removes outgoing of accepting state 2)finds roots 3) marks reachables from roots via dfs 4) prints those that were unreached (incl. the accepting state itself). 

#include <stdlib.h>
#include <stdio.h>
#include <vector>

int numOfVertices, current_state; 
bool **matrix;
bool *visited;

void dfs(int s) {
	visited[s] = true;
	for (int t = 0; t < numOfVertices; ++t)
	{
		if (!visited[t] && matrix[s][t]) dfs(t);
	}
}


void print_m() {
	int s = 0, j;
	for (; s < numOfVertices; ++s) {				
		j = 0;
		for (; j < numOfVertices; ++j) {
			printf("%d ", matrix[s][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	int s = 0, j;
	FILE *in = fopen("automaton.data", "r");  
	fscanf(in, "%d", &numOfVertices );

	// initializing matrix
	matrix = new bool*[numOfVertices];
	for(int i = 0; i < numOfVertices; ++i) {
	    matrix[i] = new bool[numOfVertices];
	}

	for (int t = 0; t < numOfVertices; ++t)
		for (int j = 0; j < numOfVertices; ++j)
			matrix[t][j] = false;
	
	
	visited = new bool[numOfVertices];	
	for (int t = 0; t < numOfVertices; ++t) visited[t] = false;

	// reading input
	int i1, i2;
	for (i2 = 0 ; i2 < numOfVertices; ++i2) // finding accepting state
	{
		fscanf(in, "%d", &i1);
		if (i1) current_state = i2;   // so we're getting the last accepting state (normally there should only be 1)		  	 	  
	}

	while (!feof(in)) 
	{
		fscanf(in, "%d %d", &i1, &i2);
		if (i1 == current_state) continue; // removing outgoing edges of accepting states.
		matrix[i2][i1] = true; // reversing the edges	
	}

	// finding roots which are not accepting (in the reversed graph)
	std::vector<int> roots;	
	for (; s < numOfVertices; ++s) {
		if (s == current_state) continue;
		bool root = true;
		j = 0;
		for (; j < numOfVertices; ++j) {
			if (matrix[j][s] && s!= j) {root = false; break;}
		}
		if (root) roots.push_back(s);
	}

	// marking reachable nodes
	for (int j = 0; j < roots.size(); ++j)
		dfs(roots[j]);

	FILE *out = fopen("doomed.data", "w");

	for (int t = 0; t < numOfVertices; ++t)
	{
		if (!visited[t]) fprintf(out, "%d ", t);
	}
	fclose(out);
}
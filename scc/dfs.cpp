
// input: automaton (from automaton.data)
// output: doomed states, i.e., states that can only reach the accepting state.
// 1) reverses edges and removes outgoing of accepting state 2)finds roots 3) marks reachables from roots via dfs 4) prints those that were unreached (incl. the accepting state itself). 

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "../file_names.h"

int numOfVertices, current_state = 0; 
int **matrix;
bool *visited;

void dfs(int s) {
	visited[s] = true;
	for (int t = 0; t < numOfVertices; ++t)
	{
		if (!visited[t] && (matrix[s][t] >=0)) dfs(t);
	}
}

// can we reach target from s, without using e ? 
bool reachable_excluding_edge(int s, int e, int target) {
	if (s == target) return true;
	visited[s] = true;
	for (int t = 0; t < numOfVertices; ++t)
	{
		if (!visited[t] && (matrix[s][t] >=0) && (matrix[s][t] != e)) return reachable_excluding_edge(t, e, target);
	}
	return false;
}

void print_m() {
	int s = 0, j;
	for (; s < numOfVertices; ++s) {				
		j = 0;
		for (; j < numOfVertices; ++j) {
			printf("%3d ", matrix[s][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void reset_visited() {
	for (int t = 0; t < numOfVertices; ++t) visited[t] = false;
}

int main(int argc, char** argv) {
	int s = 0, j, alphabetSize;
	FILE *out, *in = fopen(AUTOMATON, "r");  
	fscanf(in, "%d %d", &numOfVertices, &alphabetSize );

	// initializing matrix
	matrix = new int*[numOfVertices];
	for(int i = 0; i < numOfVertices; ++i) {
	    matrix[i] = new int[numOfVertices];
	}

	for (int t = 0; t < numOfVertices; ++t)
		for (int j = 0; j < numOfVertices; ++j)
			matrix[t][j] = -1; 
	
	

	
	visited = new bool[numOfVertices];	
	reset_visited();

	// reading input
	int i1, i2, label = -1;
	for (i2 = 0 ; i2 < numOfVertices; ++i2) // finding accepting state
	{
		fscanf(in, "%d", &i1);
		if (i1) current_state = i2;   // so we're getting the last accepting state (normally there should only be 1)		  	 	  
	}

	while (!feof(in)) 
	{
		label++;
		if (fscanf(in, "%d %d", &i1, &i2) != 2) continue; // for last iteration
		if (i1 == current_state) continue; // removing outgoing edges of accepting states.		
		matrix[i2][i1] = label % alphabetSize; // note that the edges are recorded in reversed direction		
	}
	//print_m();
	// finding roots which are not accepting (in the reversed graph)
	out = fopen(ROOTS, "w");
	std::vector<int> roots;	
	for (; s < numOfVertices; ++s) {
		if (s == current_state) continue;
		bool root = true;
		j = 0;
		for (; j < numOfVertices; ++j) {
			if (matrix[j][s] >= 0 && s!= j) {root = false; break;}
		}
		if (root) {
			roots.push_back(s);
			fprintf(out, "%d ", s);
		}
	}
	fclose(out);

	// marking reachable nodes
	for (int j = 0; j < roots.size(); ++j)
		dfs(roots[j]);

	out = fopen(DOOMED, "w");

	for (int t = 0; t < numOfVertices; ++t)
	{
		if (!visited[t]) fprintf(out, "%d ", t);
	}
	fclose(out);

	out = fopen(DOMINATING_EDGES, "w");
	int target_node = 0;
	for (int excluded_edge = 0; excluded_edge < alphabetSize; ++excluded_edge) {
		reset_visited();		
		if (!reachable_excluding_edge(current_state, excluded_edge, target_node)) 
			fprintf(out, "%d ", excluded_edge);
	}
}

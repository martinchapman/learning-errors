#include "dominators.hpp"
#include "../file_names.h"
#include <stdio.h>

using namespace std;
using namespace boost;


vector<int> dominators::get_dominators() {
	return dom;
}

void dominators::find_dominators(myGraph_t myGraph, int root_idx = 0){
	cout << "Finding dominators ..." << endl;	

	dom.resize(myGraph.numOfVertices);
	G g(
		myGraph.edges.begin(), myGraph.edges.end(),
		myGraph.numOfVertices);

	typedef graph_traits<G>::vertex_descriptor Vertex;
	typedef property_map<G, vertex_index_t>::type IndexMap;
	typedef
		iterator_property_map<vector<Vertex>::iterator, IndexMap>
		PredMap;

	vector<Vertex> domTreePredVector, domTreePredVector2;
	IndexMap indexMap(get(vertex_index, g));
	graph_traits<G>::vertex_iterator uItr, uEnd;
	int j = 0;
	for (boost::tie(uItr, uEnd) = vertices(g); uItr != uEnd; ++uItr, ++j)
	{
		put(indexMap, *uItr, j);
	}

	// Lengauer-Tarjan dominator tree algorithm
	domTreePredVector =	vector<Vertex>(num_vertices(g), graph_traits<G>::null_vertex());
	PredMap domTreePredMap = make_iterator_property_map(domTreePredVector.begin(), indexMap);

	Vertex root = vertex(root_idx, g);
	lengauer_tarjan_dominator_tree(g, root, domTreePredMap);

	for (boost::tie(uItr, uEnd) = vertices(g); uItr != uEnd; ++uItr)
	{
		if (get(domTreePredMap, *uItr) != graph_traits<G>::null_vertex())
			dom[get(indexMap, *uItr)] =	get(indexMap, get(domTreePredMap, *uItr));
		else
			dom[get(indexMap, *uItr)] = (numeric_limits<int>::max)();
	}

	copy(dom.begin(), dom.end(), ostream_iterator<int>(cout, " "));	
}


void dominators::print(int target) {
	int current_state = target;
	if (current_state < 0) return;
	cout << endl << "dominators of " << current_state << ":" << endl;

	FILE *out = fopen(DOMINATORS,"w");
	while(current_state != (numeric_limits<int>::max)()) {		
		fprintf(out, "%d ", current_state);
		cout << current_state << ",";
		current_state = dom[current_state];
	}
	cout << endl;
	fclose(out);
	cout << "Wrote list of dominators to " << DOMINATORS << endl;
}

bool dominators::isDom(int src, int target) {
	int current_state = target;

	while(current_state != (numeric_limits<int>::max)()) {		
		if (current_state == src) return true;
		current_state = dom[current_state];
	}
	return false;
}

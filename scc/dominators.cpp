#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dominator_tree.hpp>
#include "../file_names.h"
#include <fstream>

using namespace std;
using namespace boost;

class dominators {
	
public:	

	struct myGraph_t
	{
		typedef pair<int, int> edge;	

		int numOfVertices;
		vector<edge> edges;	
	};


	typedef adjacency_list<
		listS,
		listS,
		bidirectionalS,
		property<vertex_index_t, std::size_t>, no_property> G;

	myGraph_t myGraph;
	vector<int> dom;
	int target;

	dominators(){target = -1;} // constructor
	void populate();
	void find_dominators();
	void print();
};

void dominators::populate(){
	typedef myGraph_t::edge edge;
	int i1, i2;
	FILE *in = fopen(AUTOMATON, "r");

	fscanf(in, "%d %d", &(myGraph.numOfVertices), &i1); // i1 will not be used (it is the size of the alphabet, which we do not use).

	for (i2 = 0 ; i2 < myGraph.numOfVertices; ++i2) // finding accepting state
	{
		fscanf(in, "%d", &i1);
		if (i1) target = i2;   // so we're getting the last accepting state (normally there should only be 1)		  	 	  
	}
	
	while (!feof(in)) 
	{
		fscanf(in, "%d %d", &i1, &i2);
		myGraph.edges.push_back(edge(i1, i2));
	}
}


void dominators::find_dominators(){
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
	
	Vertex root = vertex(0, g);
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


void dominators::print() {
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


int main()
{
	dominators dom;
	
	dom.populate();	
	
	dom.find_dominators();
	
	dom.print();

	return 0;
}

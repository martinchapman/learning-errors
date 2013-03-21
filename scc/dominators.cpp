//=======================================================================
// Copyright (C) 2005 Jong Soo Park <jongsoo.park -at- gmail.com>
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/test/minimal.hpp>
#include <iostream>
//#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dominator_tree.hpp>
#include "../file_names.h"
#include <fstream>

using namespace std;

struct DominatorCorrectnessTestSet
{
	typedef pair<int, int> edge;

	int numOfVertices;
	vector<edge> edges;
	vector<int> correctIdoms;
};

using namespace boost;

typedef adjacency_list<
	listS,
	listS,
	bidirectionalS,
	property<vertex_index_t, std::size_t>, no_property> G;

int test_main(int, char*[])
{
	typedef DominatorCorrectnessTestSet::edge edge;
	DominatorCorrectnessTestSet testSet;
	int current_state = 0;
	int i1, i2;

	FILE *in = fopen(AUTOMATON, "r");

	fscanf(in, "%d %d", &testSet.numOfVertices, &i1); // i1 will not be used (it is the size of the alphabet, which we do not use).

	
	for (i2 = 0 ; i2 < testSet.numOfVertices; ++i2) // finding accepting state
	{
		fscanf(in, "%d", &i1);
		if (i1) current_state = i2;   // so we're getting the last accepting state (normally there should only be 1)		  	 	  
	}
	//cout << "accepting state = " << current_state << endl; 
	while (!feof(in)) 
	{
		fscanf(in, "%d %d", &i1, &i2);
		//cout << i1 << " " << i2 << endl;
		testSet.edges.push_back(edge(i1, i2));
	}

	cout << "Finding dominators ..." << endl;
	const int numOfVertices = testSet.numOfVertices;

	G g(
		testSet.edges.begin(), testSet.edges.end(),
		numOfVertices);

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
	domTreePredVector =
		vector<Vertex>(num_vertices(g), graph_traits<G>::null_vertex());
	PredMap domTreePredMap =
		make_iterator_property_map(domTreePredVector.begin(), indexMap);

	lengauer_tarjan_dominator_tree(g, vertex(0, g), domTreePredMap);

	vector<int> idom(num_vertices(g));
	for (boost::tie(uItr, uEnd) = vertices(g); uItr != uEnd; ++uItr)
	{
		if (get(domTreePredMap, *uItr) != graph_traits<G>::null_vertex())
			idom[get(indexMap, *uItr)] =
			get(indexMap, get(domTreePredMap, *uItr));
		else
			idom[get(indexMap, *uItr)] = (numeric_limits<int>::max)();
	}

	copy(idom.begin(), idom.end(), ostream_iterator<int>(cout, " "));


	cout << endl << "dominators of " << current_state << ":" << endl;

	FILE *out = fopen(DOMINATORS,"w");
	while(current_state != (numeric_limits<int>::max)()) {		
		fprintf(out, "%d ", current_state);
		cout << current_state << ",";
		current_state = idom[current_state];
	}
	cout << endl;
	fclose(out);
	cout << "Wrote list of dominators to " << DOMINATORS << endl;

	return 0;
}

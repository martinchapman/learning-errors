#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dominator_tree.hpp>

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


	vector<int> dom;

	void find_dominators(myGraph_t myGraph, int root_idx);
	vector<int> get_dominators();
	void print(int target);
	bool isDom(int src, int target);
};

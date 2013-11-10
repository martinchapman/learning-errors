#define _CRT_SECURE_NO_DEPRECATE
// to get the cfg for multiple files do goto-cl file1.c file2.c; it generates file1.exe with all. Then goto-instrument --dot produces all. 
// current problem: need to connect the 'End of Function' nodes to the output of the functions. 
// can do 
// grep -A 2 subgraph tmp1.dot && grep "End of Function" tmp1.dot 
// to get all information. 

#include "../file_names.h"
#include <iostream> 
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <functional>
#include <string>
#include <set>

using namespace std;

set<int> interesting;
struct edge {char s[100]; char t[100];};
string input_file_name("try1");
map<string, int> node_index, func_index;
int numInteresting;

bool *visited;

bool **cfg_matrix;
bool **matrix;
int numOfVertices;



void print_cfg_matrix() {
	cout << " -------------------------------------------------" << endl << "   ";
		for (int t = 0; t < numOfVertices; ++t) printf("%2d", t ); cout << endl;
	for (int t = 0; t < numOfVertices; ++t){
		{
			printf("%2d:", t) ;		
			for (int j = 0; j < numOfVertices; ++j)
				printf("%2d", cfg_matrix[t][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void print_matrix() {
	
	cout << " -------------------------------------------------" << endl;
	for (int t = 0; t < numInteresting; ++t){
		for (int j = 0; j < numInteresting; ++j)
			cout << matrix[t][j] << " ";
		cout << endl;
	}
	cout << endl;
}



inline unsigned CountWords( const string& s ) {
  string x = s;
  replace_if( x.begin(), x.end(), std::ptr_fun <int, int> ( std::isspace ), ' ' );
  x.erase( 0, x.find_first_not_of( " " ) );
  if (x.empty()) return 0;
  return count( x.begin(), std::unique( x.begin(), x.end() ), ' ' ) + !std::isspace( *s.rbegin() );
}


void reachable (int src, int current, bool initCall) {

	if (visited[current]) return;
	if (!initCall) 
	{ 
		visited[current] = true;
		if (interesting.find(current) != interesting.end()) { matrix[src][current] = 1; return;}
	}
	for (int i = 0 ; i < numOfVertices; ++i ) 
		if (cfg_matrix[current][i]) reachable(src, i, false);
}

void compute_reachable() {
	set<int>::iterator it;
	
	for (it = interesting.begin(); it != interesting.end(); ++it) {
		for (int i = 0; i < numOfVertices; ++i) visited[i] = false;
		reachable(*it, *it, true);
	}
	print_matrix();
}



void print_edges(vector<edge> edge_list) {
	vector<edge>::iterator it;
	cout << "Edge list = " << endl;
	for (it = edge_list.begin(); it < edge_list.end(); ++it)
	{
		cout << (*it).s << " " << (*it).t << endl;
	}

}

// cfg_edges.dat contains 2 types of lines:
// n1 n2   -- these are edges between non-function nodes 
// n1 n2 func_name -- these are edges to functions
int read_cfg_edges( vector<edge> *edge_list) {
	edge tmp_edge;	
	char line[200],func_name[100];

	FILE *edges = fopen(CFG_EDGES, "r");
	if (edges == NULL) {fprintf(stderr, "cannot open %s\n", CFG_EDGES); exit(1);}
	while(!feof(edges)) {
		fgets(line, 200, edges);
		int count = CountWords(line);
		if (count == 2) sscanf(line, "%s %s", tmp_edge.s, tmp_edge.t); 
		else 
		{
			sscanf(line, "%s %s %s", tmp_edge.s, tmp_edge.t, func_name); 
			strcpy(tmp_edge.t, func_name);
		}		
		(*edge_list).push_back(tmp_edge);
		pair<map<string, int>::iterator,bool> res;
		node_index.insert(pair<string, int> (string(tmp_edge.s), node_index.size()));		
		res = node_index.insert(pair<string, int> (string(tmp_edge.t), node_index.size()));
		if (count == 3) {			
			func_index.insert(pair<string, int> (string(func_name), res.first -> second)); // res.first is the pair inserted. res.first -> second gives us the value with which the element was inserted.
		}		
	}
	return (node_index.size());
}

void read_cfg_connectors(vector<edge> *edge_list) {
	edge tmp_edge;		
	int size = (*edge_list).size();
	FILE *connectors = fopen(CFG_CONNECTORS, "r");
	if (connectors == NULL) {fprintf(stderr, "cannot open %s\n", CFG_CONNECTORS); exit(1);}
	while(!feof(connectors)) {
		if (fscanf(connectors, "%s %s", tmp_edge.s, tmp_edge.t) != 2) continue;  
		(*edge_list).push_back(tmp_edge);
	}
	size = (*edge_list).size() - size ;
	cout << "added " << size << "edges" << endl;
}

int generate_func_names(int letter) {
	// 1) fills the global list node_index with interesting nodes (from input_file_name.f)	
	
	char name[100];
	
	stringstream st;
	st << input_file_name << ".f";
	FILE *user_func_names = fopen(st.str().c_str() , "r");
	
	// populating user_func_names with function names from input_file_name.f
	if (user_func_names != NULL) {
		cout << "found " << st.str() << endl;
		while (!feof(user_func_names)) {
			if (fscanf(user_func_names, "%s", name) != 1) continue;	
			node_index.insert(pair<string, int>(string(name), letter++));
		}
	}
	else cout << "Using all function names (other than 'main'). A restricted list can be given in a file " << input_file_name << ".f" << endl;
	
	return letter;
}


void main() {
	
	vector<edge> edge_list;
	stringstream st;
	
	// necessary because we need vs prompt to run goto-cl
	st << "cmd /c \"\"C:\\Program Files\ (x86)\\Microsoft\ Visual\ Studio\ 10.0\\VC\\vcvarsall.bat\" & goto-cl " << input_file_name <<".c\"";
	cout << st.str() << endl;
	system(st.str().c_str());
	
	string cmd(CFG2GRAPH + string(" ") + input_file_name + string(" ") + CFG_EDGES + string(" ") + CFG_CONNECTORS);
	
	system(cmd.c_str());

	// reading interesting nodes (supposed to be all function names)
	generate_func_names(0);
	map<string, int>::iterator func_it;

	for (func_it = node_index.begin(); func_it != node_index.end(); ++func_it) {
		cout << func_it -> first << " " << func_it -> second << endl;
		interesting.insert(func_it -> second);  
	}
	numInteresting = interesting.size();
	numOfVertices = read_cfg_edges(&edge_list);
	// cout << "After reading cfg_edges:"<< endl;
	// print_edges(edge_list);
	read_cfg_connectors(&edge_list);
	//  cout << "After connectors:"<< endl;
	// print_edges(edge_list);
		
	visited = new bool[numOfVertices];
	cout << "# of vertices = " << numOfVertices << endl;

	// initializing cfg_matrix
	cfg_matrix = new bool*[numOfVertices];
	for(int i = 0; i < numOfVertices; ++i) {
	    cfg_matrix[i] = new bool[numOfVertices];
	}

	// resetting cfg_matrix
	for (int t = 0; t < numOfVertices; ++t)
		for (int j = 0; j < numOfVertices; ++j)
			cfg_matrix[t][j] = false;


	matrix = new bool*[numInteresting]; // to be replaced
	for(int i = 0; i < numInteresting; ++i) {
	    matrix[i] = new bool[numInteresting];
	}
	// resetting matrix
	for (int t = 0; t < numInteresting; ++t)
		for (int j = 0; j < numInteresting; ++j)
			matrix[t][j] = false;
	

	// filling cfg_matrix
	vector<edge>::iterator it;
	for (it = edge_list.begin(); it != edge_list.end(); ++it) {
		int src = node_index[(*it).s];
		int target = node_index[(*it).t];
		cout << src << " " << (*it).s << " " << target << " " << (*it).t << endl;
		cfg_matrix[src][target] = true;
	}

	


//	print_cfg_matrix(); 
	compute_reachable();

	
}
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
#define inter 6

using namespace std;

set<int> interesting;
struct edge {char s[100]; char t[100];};
string input_file_name("try_nondet");
map<string, int> node_index, func_index;


bool *visited;

bool **cfg_matrix;
bool **matrix;
int numOfVertices;



void print_cfg_matrix() {
	cout << " -------------------------------------------------" << endl;
	for (int t = 0; t < numOfVertices; ++t){
		for (int j = 0; j < numOfVertices; ++j)
			cout << cfg_matrix[t][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void print_matrix() {
	cout << " -------------------------------------------------" << endl;
	for (int t = 0; t < inter; ++t){
		for (int j = 0; j < inter; ++j)
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


void reachable (int src, int current) {

	if (visited[current]) return;
	visited[current] = true;
	if ((src != current) && interesting.find(current) != interesting.end()) { matrix[src][current] = 1; return;}
	for (int i = 0 ; i < numOfVertices; ++i ) 
		if (cfg_matrix[current][i]) reachable(src, i);
}

void compute_reachable() {
	set<int>::iterator it;
	
	for (it = interesting.begin(); it != interesting.end(); ++it) {
		for (int i = 0; i < numOfVertices; ++i) visited[i] = false;
		reachable(*it, *it);
	}
	print_matrix();
}

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
	// reads func names from FUNC_NAMES and 
	// 1) fills the global list node_index (to be used later in compute_allowed_pairs())
	// 2) populates AUTO_LABELS_FUNCTIONS with function labels, 
	// 3) prepares the CONVERT (convert.bat) file, which removes calls to _Learn_func_enter that we are not interested in (e.g. 'main, check_conjectiure, etc), 
	//    and replaces the (char *) <func_name> with (int) index in the file a.c (the result of goto-instrument). Using int rather than strings avoids
	//    strcmp() instructions which turn into loops. 
	char name[100];
	map<string, int> user_func_set;
	stringstream st;
	st << input_file_name << ".f";
	FILE *func_names = fopen(FUNC_NAMES, "r"),
		*Labels = fopen(AUTO_LABELS_FUNCTIONS, "w"),
		*user_func_names = fopen(st.str().c_str() , "r");
	if (func_names == NULL) {fprintf(stderr, "cannot open %s. ", FUNC_NAMES); exit(1);}
	if (user_func_names != NULL) {
		cout << "found " << st.str() << endl;
		while (!feof(user_func_names)) {
			if (fscanf(user_func_names, "%s", name) != 1) continue;
			user_func_set.insert(pair<string, int>(name, 0));
		}
	}
	else cout << "Using all function names (other than 'main'). A restricted list can be given in a file " << input_file_name << ".f" << endl;
	bool first = true;
	while (!feof(func_names)) {
		if (fscanf(func_names, "%s", name) != 1) continue;

		if (!strcmp(name, "main") || ((user_func_names != NULL) && user_func_set.find(name) == user_func_set.end())) // here we can add other functions we wish to ignore
		{
			//cout << "skipping " << name << endl; 
			//rewrite_function_enter(name, -1); // -1 = remove statement
			continue; 
		}		
		first = false;
		node_index.insert(pair<string, int>(string(name), letter));
		fprintf(Labels, "%d %s\n", letter, name);
		letter ++;
		//rewrite_function_enter(name, letter++);		
	}
	// what's special about assert is that it is not instrumented, being a library function. Inside Learn_assert we invoke Learn(alphabet-1)
#ifdef USE_ASSERT_LETTER
	fprintf(Labels, "%d %s\n", letter, "assert");
	node_index.insert(pair<string, int>(string("assert"), letter++));	
#endif	

	fclose(func_names);
	fclose(Labels);	
	return letter;
}


void main() {
	
	vector<edge> edge_list;
	stringstream st;
	
	//st << "cmd /c \"goto-cl " << input_file_name <<".c\"";
	//system(st.str().c_str());

	string cmd(CFG2GRAPH + string(" ") + input_file_name + string(" ") + CFG_EDGES + string(" ") + CFG_CONNECTORS);
	
	system(cmd.c_str());

	generate_func_names(0);
	map<string, int>::iterator func_it;

	for (func_it = node_index.begin(); func_it != node_index.end(); ++func_it) {
		cout << func_it -> first << " " << func_it -> second << endl;
		interesting.insert(func_it -> second);  // to be replaced with the interesting edges.
	}

	numOfVertices = read_cfg_edges(&edge_list);
	read_cfg_connectors(&edge_list);

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


	matrix = new bool*[inter]; // to be replaced
	for(int i = 0; i < inter; ++i) {
	    matrix[i] = new bool[inter];
	}
	// resetting matrix
	for (int t = 0; t < inter; ++t)
		for (int j = 0; j < inter; ++j)
			matrix[t][j] = false;
	

	// filling cfg_matrix
	vector<edge>::iterator it;
	for (it = edge_list.begin(); it != edge_list.end(); ++it) {
		int src = node_index[(*it).s];
		int target = node_index[(*it).t];
		cout << src << " " << (*it).s << " " << target << " " << (*it).t << endl;
		cfg_matrix[src][target] = true;
	}

	


	print_cfg_matrix(); 
	compute_reachable();

	
}
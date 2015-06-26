/* $Id: conjecture.cpp 1430 2011-01-24 16:41:34Z davidpiegdon $
 * vim: fdm=marker
 *
 * This file is part of libalf.
 *
 * libalf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libalf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libalf.  If not, see <http://www.gnu.org/licenses/>.
 *
 * (c) 2008,2009,2010 Lehrstuhl Softwaremodellierung und Verifikation (I2), RWTH Aachen University
 *                and Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 * Author: David R. Piegdon <david-i2@piegdon.de>
 *
 */

#include <set>
#include <map>
#include <list>
#include <queue>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <winsock.h>
#include <stdint.h>
#include <stdio.h>
#else
#include <arpa/inet.h>
#endif

#include <stdlib.h>
#include <iostream> // ~MDC
#include <list> // ~MDC
#include <stack> // ~MDC
#include <assert.h>
#include "libalf/conjecture.h"
#include "libalf/serialize.h"
#include "../../../file_names.h" // ofer
#include<string.h>

namespace libalf {
    
using namespace std;



// helper-functions for human-readable parser:
static string parser_split_line(string & blob)
{{{
	int p;
	string tmp, ret;

	// split first line off.
	p = blob.find_first_of('\n');
	tmp = blob.substr(0, p);
	blob = blob.substr(p+1, string::npos);

	// remove comments
	tmp = tmp.substr(0, tmp.find_first_of('#'));

	// strip superficial whitespace et al
	bool front=true;
	bool white=false;
	for(size_t i = 0; i < tmp.size(); i++) {
		switch (tmp[i]) {
			case ' ':
			case '\f':
			case '\n':
			case '\r':
			case '\t':
			case '\v':
				if(!front && !white) {
					ret.push_back(' ');
					white = true;
				}
				break;
			case ';':
			case '=':
			case ',':
			case '[':
			case ']':
				if(front) {
					ret.push_back(tmp[i]);
				} else {
					if(white) {
						ret[ret.size()-1] = tmp[i];
					} else {
						ret.push_back(tmp[i]);
					}
				}
				front = true;
				white = false;
				break;
			default:
				ret.push_back(tolower(tmp[i]));
				front = false;
				white = false;
				break;
		}
	}

	// remove white-space at EOL
	if(white)
		ret = ret.substr(0, ret.size()-1);

	// if this line is empty, try next line
	if(ret.empty() && !blob.empty())
		return parser_split_line(blob);
	else
		return ret;
}}}
static bool parser_get_set(string single, set<int>& s)
{{{
	while(1) {
		string num;
		size_t p;
		p = single.find_first_of(',');
		num = single.substr(0, p);
		if(p != string::npos) {
			single = single.substr(p+1, string::npos);
		} else {
			single="";
		}
		if(num == "") {
			break;
		} else {
			int n;
			char * endptr;
			n = strtol(num.c_str(), &endptr, 10);
			if(*endptr)
				return false;
			s.insert(n);
		}
	}

	return true;
}}}




bool finite_automaton::calc_validity()
{{{
	if(!moore_machine<bool>::calc_validity())
		goto invalid;

	if(this->omega)
		goto invalid;

	return true;

invalid:
	this->valid = false;
	return false;
}}}
basic_string<int32_t> finite_automaton::serialize() const
{{{
	// CUSTOM FORMAT, to match libAMoRE++ serialization format.

	basic_string<int32_t> ret;

	if(this->valid) {
		ret += 0; // size, filled in later.
		ret += ::serialize(this->is_deterministic);
		ret += ::serialize(this->input_alphabet_size);
		ret += ::serialize(this->state_count);
		ret += ::serialize(this->initial_states);

		// get final states
		set<int> final;
		map<int, bool>::const_iterator mi;
		for(mi = this->output_mapping.begin(); mi != this->output_mapping.end(); ++mi)
			if(mi->second)
				final.insert(mi->first);
		ret += ::serialize(final);

		// get transitions
		int transition_count = 0;
		basic_string<int32_t> transition_ser;
		map<int, map<int, set<int> > >::const_iterator mmsi;
		map<int, set<int> >::const_iterator msi;
		set<int>::const_iterator si;

		for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi) {
			for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi) {
				for(si = msi->second.begin(); si != msi->second.end(); ++si) {
					++transition_count;
					transition_ser += ::serialize(mmsi->first); // src
					transition_ser += ::serialize(msi->first); // label
					transition_ser += ::serialize(*si); // dst
				}
			}
		}
		ret += ::serialize(transition_count);
		ret += transition_ser;

		ret[0] = htonl(ret.length() - 1);
	}

	return ret;
}}}
bool finite_automaton::deserialize(serial_stretch & serial)
{{{
	int size;
	int transition_count;
	int i;
	int src, label, dst;

	set<int> final;
	set<int>::const_iterator si;

	clear();
	if(!::deserialize(size, serial)) goto invalid;
	if(!::deserialize(this->is_deterministic, serial)) goto invalid;
	if(!::deserialize(this->input_alphabet_size, serial)) goto invalid;
	if(!::deserialize(this->state_count, serial)) goto invalid;
	if(!::deserialize(this->initial_states, serial)) goto invalid;
	// final states
	if(!::deserialize(final, serial)) goto invalid;
	for(i = 0; i < this->state_count; ++i)
		output_mapping[i] = false;
	for(si = final.begin(); si != final.end(); ++si)
		output_mapping[*si] = true;
	// transitions
	if(!::deserialize(transition_count, serial)) goto invalid;
	for(i = 0; i < transition_count; ++i) {
		if(!::deserialize(src, serial)) goto invalid;
		if(!::deserialize(label, serial)) goto invalid;
		if(!::deserialize(dst, serial)) goto invalid;
		this->transitions[src][label].insert(dst);
	}

	this->valid = true;
	return true;
invalid:
	clear();
	return false;
}}}


string finite_automaton::write() const  // ofer. Original below.
{{{
	string ret;
	FILE *analyzer, *header;
	analyzer = fopen(AUTOMATON, "w");
	header = fopen(CONJECTURE_DATA_H, "w");
	if(valid) {
		char buf[256];
		char buf_for_analyzer[256]; 
		map<int, map<int, set<int> > >::const_iterator mmsi;
		map<int, set<int> >::const_iterator msi;
		set<int>::const_iterator si;
		map<int, bool>::const_iterator oi;
		bool first_komma;
		ostringstream ab_size_s;   
		ab_size_s << this->input_alphabet_size;

		snprintf(buf, 256, "#define states %d\n", this->state_count);
		fprintf(header, "#define states %d\nextern bool accept[states];\nextern char A[states * AlphaBetSize];\n", this->state_count);
		fclose(header);

		fprintf(analyzer, "%d %d\n", this->state_count, this->input_alphabet_size);
		ret += buf;
		
		ret += "bool accept[states] = {";

		first_komma = true;
		for(oi = this->output_mapping.begin(); oi != this->output_mapping.end(); ++oi) {  // marking accepting states
			if(oi->second) {
				snprintf(buf, 256, "%s%d", first_komma ? " " : ", ", 1 /*oi->first*/);
				fprintf(analyzer, "%d ", 1 /*oi->first*/); // accepting
				first_komma = false;
				ret += buf;				
			}
			else 
			{
				snprintf(buf, 256, "%s0", first_komma ? " " : ", ");
				fprintf(analyzer, "0 "); // non-accepting
				first_komma = false;
				ret += buf;				
			}
			
		}
		fprintf(analyzer,"\n");
		ret += "};\n";
		
		ret += "char A[states * " + ab_size_s.str() + "] = {";
		first_komma = true;
		int i=0;
		for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi, ++i) {
			//ret += "{";
			for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi) {				
				for(si = msi->second.begin(); si != msi->second.end(); ++si) {
					snprintf(buf, 256, "%s %d ",  first_komma ? " " : ", ", *si);
					fprintf(analyzer, "%d %d\n",  i, *si);
					first_komma = false;
					ret += buf;					
				}				
			}
			//ret += "}";
		}
		ret += "};";
	}

	fclose(analyzer);
	
	return ret;
}}}
    
/* original:


string finite_automaton::write() const
{{{
	string ret;

	if(valid) {
		char buf[256];
		map<int, map<int, set<int> > >::const_iterator mmsi;
		map<int, set<int> >::const_iterator msi;
		set<int>::const_iterator si;
		map<int, bool>::const_iterator oi;
		bool first_komma;

		snprintf(buf, 256, "[general]\n"
				   "\tis dfa = %s;\n"
				   "\talphabet size = %d;\n"
				   "\tnumber of states = %d;\n"
				   "[initial states]\n",
				this->is_deterministic ? "true" : "false", this->input_alphabet_size, this->state_count);
		ret += buf;

		first_komma = true;
		for(si = this->initial_states.begin(); si != this->initial_states.end(); ++si) {
			snprintf(buf, 256, "%s%d", first_komma ? "\t" : ", ", *si);
			first_komma = false;
			ret += buf;
		}
		if(!first_komma)
			ret += ";";

		ret += "\n[final states]\n";

		first_komma = true;
		for(oi = this->output_mapping.begin(); oi != this->output_mapping.end(); ++oi) {
			if(oi->second) {
				snprintf(buf, 256, "%s%d", first_komma ? "\t" : ", ", oi->first);
				first_komma = false;
				ret += buf;
			}
		}
		if(!first_komma)
			ret += ";";

		ret += "\n[transitions]\n";

		for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi) {
			for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi) {
				for(si = msi->second.begin(); si != msi->second.end(); ++si) {
					snprintf(buf, 256, "\t%d, %d, %d;\n", mmsi->first, msi->first, *si);
					ret += buf;
				}
			}
		}
	}

	return ret;
}}}
*/

string finite_automaton::write_min() const  //ofer
{{{
	string ret;

	return " ";

	if(valid) {
		char buf[256];
		map<int, map<int, set<int> > >::const_iterator mmsi;
		map<int, set<int> >::const_iterator msi;
		set<int>::const_iterator si;
		map<int, bool>::const_iterator oi;
		bool first_komma;

		/*snprintf(buf, 256, "[general]\n"
				   "\tis dfa = %s;\n"
				   "\talphabet size = %d;\n"
				   "\tnumber of states = %d;\n"
				   "[initial states]\n",
				this->is_deterministic ? "true" : "false", this->input_alphabet_size, this->state_count);*/
		snprintf(buf, 256, "#define states %d\n", this->state_count);

		ret += buf;

	/*	first_komma = true;
		for(si = this->initial_states.begin(); si != this->initial_states.end(); ++si) {
			snprintf(buf, 256, "%s%d", first_komma ? "\t" : ", ", *si);
			first_komma = false;
			ret += buf;
		}
		if(!first_komma)
			ret += ";";

		ret += "\n[final states]\n";*/
		ret += "bool accept[states] = {";
		/*
		first_komma = true;
		for(oi = this->output_mapping.begin(); oi != this->output_mapping.end(); ++oi) {
			if(oi->second) {
				snprintf(buf, 256, "%s%d", first_komma ? " " : ", ", oi->first);
				first_komma = false;
				ret += buf;
			}
			
		}
		
		ret += "};\n";

		ret += "char A[states][2] = {\n";

		for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi) {
			for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi) {
				ret += "{";
				for(si = msi->second.begin(); si != msi->second.end(); ++si) {
					snprintf(buf, 256, "\t %d\n",  *si);
					ret += buf;
				}
				ret += "}";
			}
		}*/
		ret += "};";
	}

	return ret;
}}}

int finite_automaton::count_transitions()  // ~MDC
{{{
    if ( this->edge_count != 0) return edge_count;
    
    int edges = 0;
    
    map<int, map<int, set<int> > >::const_iterator mmsi;
    map<int, set<int> >::const_iterator msi;
    set<int>::const_iterator si;
    for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi)
        for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi)
            for(si = msi->second.begin(); si != msi->second.end(); ++si)
            {
                if (this->sinks_set.find(mmsi->first)  == this->sinks_set.end() && this->sinks_set.find(*si)  == this->sinks_set.end())
                {
                    edges++;
                }
            }
    
    this->edge_count = edges;
    
    
    
    return edges;
}}}

// ~MDC Source: http://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
Graph::Graph(int V) {
    this->V = V;
    adj = new std::list<int>[V];
} 

void Graph::add_edge(int v, int w, int letter) {
    adj[v].push_back(w);
    
	pair<int,int> p(v,w); 
    edge_alphabet[p] = letter;
}
    
int Graph::edge_to_alphabet(int v, int w) {
        
    pair<int,int> p(v,w);
    return edge_alphabet[p];

}
    
int Graph::count_edges() {
    int edges = 0;
    for (int v=0; v<this->V; v++) {
        edges += adj[v].size();
    }
    return edges;
}

// finds a path from s to t, and adds it to path. 
bool Graph::get_path(int s, int t, std::list<int>& path, bool inclusive) { // inclusive = in the top recursive frame s can be the t. 
	cout << "in get_path " << s << "," << t << ", V = " << V << " inclusive = " << inclusive << endl;
	std::vector<bool>::iterator it;
	if (inclusive) {  // this condition is false only once: when starting the 2nd search from t to t. Then we do not count the source.  		
		if (s == t) return true; 		
		visited[s] = true; 
	}
	std::list<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i) 
    {
        int v;
		v = *i;  // v is current adjacent of 's'	
//		cout << "v = " << v << endl;
		if (!visited[v]) {			
			path.push_back(edge_to_alphabet(s,v));
			if (get_path(v, t, path)) return true;
		}
	}
	path.pop_back();
	return false;
}

std::list<std::list<int> > Graph::find_all_paths(int s, int t, std::list<int>& path, std::list<std::list<int> >& paths) { // ~MDC

	if (s == t) { 
		path.push_back(t);
		paths.push_back(path);
		return paths; 		
	}
	
	std::list<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
    {
        int v;
		v = *i;	
		// State calls self: do not follow this path
		if ( s == v ) continue;
		std::list<int> branch = path;
		branch.push_back(s);
		find_all_paths(v, t, branch, paths);
	}
	
	return paths;
	
} 

bool Graph::recursive_non_accepting(std::set<int> accepting) { // ~MDC
	
    for ( int v = 0; v < this->V; v++ ) {
        
		for ( std::list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i ) {
		
			if ( v == *i && std::find(accepting.begin(), accepting.end(), v) == accepting.end() ) { 
				
				return true;
				
			}
			
		}
			
    }
	
	return false;
	
} 

bool finite_automaton::recursive_non_accepting() { // ~MDC
    std::set<int> accepting = get_final_states();
	
	Graph g1(this->state_count);
    
    map<int, map<int, set<int> > >::const_iterator mmsi;
    map<int, set<int> >::const_iterator msi;
    set<int>::const_iterator si;
    for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi)
        for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi)
			for(si = msi->second.begin(); si != msi->second.end(); ++si) {
                if (this->sinks_set.find(mmsi->first)  == this->sinks_set.end() && this->sinks_set.find(*si)  == this->sinks_set.end()) {
                    g1.add_edge(mmsi->first, *si, msi->first);  // we add edges not connecting to the sink n on-accepting state. 
					//cout << mmsi->first << "-> " << *si << "[" << msi->first <<"]" << endl;
                }
            }
		
	std::set<int>::iterator it;
	bool result;
	
	for (it=initial_states.begin(); it!=initial_states.end(); ++it) {
		result = g1.recursive_non_accepting(accepting);
	}
	
	return result;    
}

std::vector<int> finite_automaton::get_transitions(int s, int t) { // ~MDC
	 std::vector<int> transitions;
	 map<int, set<int> >::const_iterator msi;
	 for(msi = this->transitions.find(s)->second.begin(); msi != this->transitions.find(s)->second.end(); ++msi) {
	     if ( std::find(msi->second.begin(), msi->second.end(), t) != msi->second.end() ) {
			 transitions.push_back(msi->first);
	     }
	 }
	 return transitions;
} 

std::vector<std::pair<int,int> > finite_automaton::nodes_connecting_letter(int a) { // ~MDC	
	
	std::vector<std::pair<int,int> > nodes_connected_by_letter;
	nodes_connected_by_letter.clear();
	
    map<int, map<int, set<int> > >::const_iterator mmsi;
    map<int, set<int> >::const_iterator msi;
    set<int>::const_iterator si;
    for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi)
        for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi)
			for(si = msi->second.begin(); si != msi->second.end(); ++si) { 
				if ( msi->first == a ) {
					if (this->sinks_set.find(mmsi->first)  == this->sinks_set.end() && this->sinks_set.find(*si)  == this->sinks_set.end()) {
						std::pair<int, int> start_end( mmsi->first, *si );
						nodes_connected_by_letter.push_back(start_end);
				    }
				}
			}
	if (nodes_connected_by_letter.size() == 0) { 
		std::pair<int, int> start_end( 0, 0 );
		nodes_connected_by_letter.push_back(start_end);
	}
	
	return nodes_connected_by_letter;
} 

bool finite_automaton::find_lasso(std::list<int>& path) {  // ofer
    std::set<int> accepting = get_final_states();
	// cout << "accepting.size = " << accepting.size() << endl;
	if (accepting.size() == 0) return false;
	assert(accepting.size() == 1);
	
	Graph g1(this->state_count);
    
    map<int, map<int, set<int> > >::const_iterator mmsi;
    map<int, set<int> >::const_iterator msi;
    set<int>::const_iterator si;
    for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi)
        for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi)
            for(si = msi->second.begin(); si != msi->second.end(); ++si)
            {
                if (this->sinks_set.find(mmsi->first)  == this->sinks_set.end() && this->sinks_set.find(*si)  == this->sinks_set.end())
                {
                    g1.add_edge(mmsi->first, *si, msi->first);  // we add edges not connecting to the sink n on-accepting state. 
					//cout << mmsi->first << "-> " << *si << "[" << msi->first <<"]" << endl;
                }
            }
		
	int target = *accepting.begin();
	std::set<int>::iterator it;
	for (it=initial_states.begin(); it!=initial_states.end(); ++it) {
		path.clear(); 
		g1.visited = std::vector<bool>(this->state_count + 1, false);
		//cout << "calling get_path (1) with " << *it << "," << target << endl;
		if (!g1.get_path(*it, target, path)) return false; 
		g1.visited = std::vector<bool>(this->state_count + 1, false);		
		//cout << "calling get_path (2) with " << target << "," << target << endl;
		if (g1.get_path(target, target, path, false)) return true;
	}
	return false;    
}

std::list<std::list<int> > finite_automaton::find_all_paths() { // ~MDC

	Graph g1(this->state_count);
    
    map<int, map<int, set<int> > >::const_iterator mmsi;
    map<int, set<int> >::const_iterator msi;
    set<int>::const_iterator si;
    for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi)
        for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi)
			for(si = msi->second.begin(); si != msi->second.end(); ++si)
				g1.add_edge(mmsi->first, *si, msi->first);
	
	std::list<std::list<int> > paths;
	
	set<int> final_states = this->get_final_states();
	
	for( set<int>::const_iterator accepting_state = final_states.begin(); accepting_state != final_states.end(); ++accepting_state ) {	
		
		std::list<int> path;
	
		for (std::set<int>::const_iterator it=initial_states.begin(); it!=initial_states.end(); ++it) {
			path.clear();
			g1.find_all_paths(*it, *accepting_state, path, paths);
		}
		
	}
	
	return paths;  
}

// ~MDC End

bool finite_automaton::read(string input)
{{{
	bool set_is_det = false, set_alphabet_size = false, set_state_count = false;
	enum section {
		section_none,
		section_general,
		section_initial,
		section_final,
		section_transitions
	} current_section = section_none;

	clear();

	// split lines
	string line, single, token;
	while(1) {
		line = parser_split_line(input);
		if(input.empty() && line.empty())
			break;

		// split semi-colons
		while(1) {
			size_t p;
			p = line.find_first_of(';');
			single = line.substr(0, p);
			line = (p == string::npos) ? "" : line = line.substr(p+1, string::npos);


			if(single.empty()) {
				if(line.empty())
					break;
			} else {
//				fprintf(stderr, "new single >>%s<<\n", single.c_str());
				if(single[0] == '[') {
					if(single[single.size()-1] != ']') {
						this->valid = false;
						goto end;
					}

					single = single.substr(1, single.size()-2);
					if(single == "general")
						current_section = section_general;
					else
						if(single == "initial states")
							current_section = section_initial;
						else
							if(single == "final states")
								current_section = section_final;
							else
								if(single == "transitions")
									current_section = section_transitions;
								else {
									this->valid = false;
									goto end;
								}
				} else {
					switch (current_section) {
						case section_none:
							this->valid = false;
							goto end;
						case section_general:
							{
								string lval, rval;
								char *endptr;
								size_t p = single.find_first_of('=');
								if(p == string::npos) {
									this->valid = false;
									goto end;
								}
								lval = single.substr(0,p);
								rval = single.substr(p+1, string::npos);
								if(lval == "is dfa") {
									if(rval == "true" || rval == "yes") {
										this->is_deterministic = true;
										set_is_det = true;
									} else {
										if(rval == "false" || rval == "no") {
											this->is_deterministic = false;
											set_is_det = true;
										} else {
											this->valid = false;
											goto end;
										}
									}
								} else {
									if(lval == "alphabet size") {
										set_alphabet_size = true;
										this->input_alphabet_size = strtol(rval.c_str(), &endptr, 10);
										if(*endptr) {
											this->valid = false;
											goto end;
										}
									} else {
										if(lval == "number of states") {
											set_state_count = true;
											this->state_count = strtol(rval.c_str(), &endptr, 10);
											// set all states to be non-final
											for(int i = 0; i < this->state_count; ++i)
												this->output_mapping[i] = false;
											if(*endptr) {
												this->valid = false;
												goto end;
											}
										} else {
											this->valid = false;
											goto end;
										}
									}
								}
							}
							break;
						case section_initial:
							if(!parser_get_set(single, this->initial_states)) {
								this->valid = false;
								goto end;
							}
							break;
						case section_final:
							{
								set<int> final;
								set<int>::iterator si;

								if(!parser_get_set(single, final)) {
									this->valid = false;
									goto end;
								}
								for(si = final.begin(); si != final.end(); ++si)
									this->output_mapping[*si] = true;
							}
							break;
						case section_transitions:
							if(!parse_transition(single)) {
								this->valid = false;
								goto end;
							}
							break;
					}
				}
			}
		}
	}

	this->valid = set_is_det && set_alphabet_size && set_state_count;

end:
	if(!valid)
		clear();

	return valid;
}}}

string finite_automaton::visualize_existing() const //~MDC
{{{
	stringstream str, tmp, dom_edges;
	
	#define MaxAlphabet 200
	
	if (valid) {
		
		set<int>::iterator sti;
		bool header_written;

		// head
		str << "digraph finite_automaton {\n"
			"\tgraph[fontsize=8]\n"
			"\trankdir=LR;\n"
			"\tsize=8;\n\n";

		// dominating_edges_set
		dom_edges << "node [shape=rectangle, color = green, label= \"Dominating edges: ";
		bool first = true;
		for (set<int>::iterator it = dominating_edges_set.begin(); it != dominating_edges_set.end(); ++it)
		{
			if (!first) dom_edges << ", ";
			first = false;
			dom_edges << this->label.find(*it)->second;
		}
		dom_edges << "\"]; dom_edges;\n";
		str << dom_edges.str();

		// mark final states
		header_written = false;

		int final_state_count = 0;
		map<int, bool>::const_iterator oi;

		// final states
		for(oi = output_mapping.begin(); oi != output_mapping.end(); ++oi) {
			if(oi->second) {
				++final_state_count;
				if(!header_written) {
					str << "\tnode [shape=doublecircle, style=\"\", color=green, label = \"D\"];"; // accepting states are always dominators + Doomed
					header_written = true;
				}
				str << " q" << oi->first;
			}
		}
		if(header_written)
			str << ";\n";

		// normal states

		if(final_state_count < state_count) {					
			for(oi = output_mapping.begin(); oi != output_mapping.end(); ++oi)
				if(!oi->second && sinks_set.find(oi->first)  == sinks_set.end())
				{					
					string color = (dominator_set.find(oi->first) != dominator_set.end())? "green" : "black";
					string label = (doomed_set.find(oi->first) != doomed_set.end())? "D" : "\"\"";
					tmp << "\tnode [shape=circle, style=\"\", color=" << color << ", label = " << label << "]; q" << oi->first << ";" << endl;
				}
		}


		str << tmp.str(); 

		// non-visible states for arrows to initial states
		header_written = false;
		for(sti = this->initial_states.begin(); sti != this->initial_states.end(); ++sti) {
			if(!header_written) {
				str << "\tnode [shape=plaintext, label=\"\", style=\"\"];";
				header_written = true;
			}
			str << " iq" << *sti;
		}
		if(header_written)
			str << ";\n";

		// and arrows to mark initial states
		for(sti = this->initial_states.begin(); sti != this->initial_states.end(); ++sti)
			str << "\tiq" << *sti << " -> q" << *sti << " [color=blue];\n";

		// transitions
		map<int, map<int, set<int> > >::const_iterator mmsi;
		map<int, set<int> >::const_iterator msi;
		set<int>::const_iterator si;
		for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi)
			for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi)
				for(si = msi->second.begin(); si != msi->second.end(); ++si)
				{
					if (this->sinks_set.find(mmsi->first)  == sinks_set.end() && sinks_set.find(*si)  == sinks_set.end()) // edge is not from/to a sink unaccepting state.
					{
						string color = (dominating_edges_set.find(msi->first) != dominating_edges_set.end()) ? ", color = green": "";
						str << "\tq" << mmsi->first << " -> q" << *si << " [label=\"" << this->label.find(msi->first)->second << "\"" << color << "];\n";
					}
				}

		// end
		str << "};\n";
	}

	return str.str();
		
}}}

string finite_automaton::visualize() const  // ofer
{{{
    stringstream str, tmp, dom_edges;
    int v;
    set<int> dominator_set, sinks_set, doomed_set, dominating_edges_set;
#define MaxAlphabet 200
    char * label[MaxAlphabet]; // 200 = max alphabet size. // should replace this with a map

    if(valid) {
        FILE *dominators = fopen(DOMINATORS, "r");
        if (dominators )
        {
            while (!feof(dominators))
            {
                fscanf(dominators, "%d", &v);
                dominator_set.insert(v);
            }
            fclose(dominators);
            printf("read %s with %d dominators\n", DOMINATORS, dominator_set.size() );
        }


        FILE *doomed = fopen(DOOMED, "r");
        if (doomed) {
            while (!feof(doomed))
            {
                fscanf(doomed, "%d", &v);
                doomed_set.insert(v);
            }
            fclose(doomed);
            printf("read %s with %d doomed\n", DOOMED, doomed_set.size() );
        }

        for (int i = 0; i < MaxAlphabet; ++i) { // just in case not all labels are defined, we default them to their numeric value.
            label[i] = (char *)malloc(3);
            sprintf(label[i], "%d", i);
        }
        char file[30] = AUTO_LABELS;
        FILE *labels = fopen(file, "r");
        if (labels == NULL) {
            strcpy(file, LABELS);
            labels = fopen(LABELS, "r");
            if (labels) printf("*** Note: using labels from %s ***\n", LABELS);
        }
        if (labels) {
            char s[100]; // max label length imagined
            int j = 0;
            while (!feof(labels))
            {
                if (fscanf(labels, "%d %s", &v, s) < 2) continue; // {fprintf(stderr, "failed to read labels file\n"); exit(1);}
                label[v] = strdup(s);
                ++j;
            }
            printf("read %s with %d labels\n", file, j);
        }

        FILE *sinks = fopen(SINKS, "r");
        if (sinks) {
            while (!feof(sinks ))
            {
                if (fscanf(sinks , "%d", &v) != 1) continue;
                sinks_set.insert(v);
            }
            fclose(sinks );
            printf("read %s with %d sinks \n", SINKS, sinks_set.size() );
        }


        FILE *dominating_edges = fopen(DOMINATING_EDGES, "r");
        if (dominating_edges) {
            while (!feof(dominating_edges ))
            {
                if (fscanf(dominating_edges , "%d", &v) != 1) continue;
                dominating_edges_set.insert(v);
            }
            fclose(dominating_edges);
            printf("read %s with %d dominating edges \n", DOMINATING_EDGES, dominating_edges_set.size() );
        }


        set<int>::iterator sti;
        bool header_written;

        // head
        str << "digraph finite_automaton {\n"
            "\tgraph[fontsize=8]\n"
            "\trankdir=LR;\n"
            "\tsize=8;\n\n";

        // dominating_edges_set
        dom_edges << "node [shape=rectangle, color = green, label= \"Dominating edges: ";
        bool first = true;
        for (set<int>::iterator it = dominating_edges_set.begin(); it != dominating_edges_set.end(); ++it)
        {
            if (!first) dom_edges << ", ";
            first = false;
            dom_edges << label[*it];
        }
        dom_edges << "\"]; dom_edges;\n";
        str << dom_edges.str();

        // mark final states
        header_written = false;

        int final_state_count = 0;
        map<int, bool>::const_iterator oi;

        // final states
        for(oi = output_mapping.begin(); oi != output_mapping.end(); ++oi) {
            if(oi->second) {
                ++final_state_count;
                if(!header_written) {
                    str << "\tnode [shape=doublecircle, style=\"\", color=green, label = \"D\"];"; // accepting states are always dominators + Doomed
                    header_written = true;
                }
                str << " q" << oi->first;
            }
        }
        if(header_written)
            str << ";\n";

        // normal states

        if(final_state_count < state_count) {
            for(oi = output_mapping.begin(); oi != output_mapping.end(); ++oi)
                if(!oi->second && sinks_set.find(oi->first)  == sinks_set.end())
                {
                    string color = (dominator_set.find(oi->first) != dominator_set.end())? "green" : "black";
                    string label = (doomed_set.find(oi->first) != doomed_set.end())? "D" : "\"\"";
                    tmp << "\tnode [shape=circle, style=\"\", color=" << color << ", label = " << label << "]; q" << oi->first << ";" << endl;
                }
        }


        str << tmp.str();

        // non-visible states for arrows to initial states
        header_written = false;
        for(sti = this->initial_states.begin(); sti != this->initial_states.end(); ++sti) {
            if(!header_written) {
                str << "\tnode [shape=plaintext, label=\"\", style=\"\"];";
                header_written = true;
            }
            str << " iq" << *sti;
        }
        if(header_written)
            str << ";\n";

        // and arrows to mark initial states
        for(sti = this->initial_states.begin(); sti != this->initial_states.end(); ++sti)
            str << "\tiq" << *sti << " -> q" << *sti << " [color=blue];\n";

        // transitions
        map<int, map<int, set<int> > >::const_iterator mmsi;
        map<int, set<int> >::const_iterator msi;
        set<int>::const_iterator si;
        for(mmsi = this->transitions.begin(); mmsi != this->transitions.end(); ++mmsi)
            for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi)
                for(si = msi->second.begin(); si != msi->second.end(); ++si)
                {
                    if (sinks_set.find(mmsi->first)  == sinks_set.end() && sinks_set.find(*si)  == sinks_set.end()) // edge is not from/to a sink unaccepting state.
                    {
                        string color = (dominating_edges_set.find(msi->first) != dominating_edges_set.end()) ? ", color = green": "";
                        str << "\tq" << mmsi->first << " -> q" << *si << " [label=\"" << label[msi->first] << "\"" << color << "];\n";
                    }
                }

        // end
        str << "};\n";
    }

    return str.str();
}}}
    
void finite_automaton::store_file_data() { //~MDC
    
    int v;
	
	if (this->sinks_set.size() == 0) {
	    FILE *sinks = fopen(SINKS, "r");
	    if (sinks) {
	        while (!feof(sinks ))
	        {
	            if (fscanf(sinks , "%d", &v) != 1) continue;
	            this->sinks_set.insert(v);
	        }
	        fclose(sinks);
	        printf("read %s with %d sinks \n", SINKS, this->sinks_set.size() );
	    }
	}
	
	if (this->label.size() == 0) {
		for (int i = 0; i < 200; ++i) { // just in case not all labels are defined, we default them to their numeric value.
			this->label[i] = (char *)malloc(3);
			sprintf(this->label[i], "%d", i); 
		}
		char file[30] = AUTO_LABELS;
		FILE *labels = fopen(file, "r");
		if (labels == NULL) {
			strcpy(file, LABELS);
			labels = fopen(LABELS, "r");
			if (labels) printf("*** Note: using labels from %s ***\n", LABELS);
		}
		if (labels) {
			char s[100]; // max label length imagined
			int j = 0;
			while (!feof(labels))
			{
				if (fscanf(labels, "%d %s", &v, s) < 2) continue; // {fprintf(stderr, "failed to read labels file\n"); exit(1);}
				this->label[v] = strdup(s); 
				++j;
			}
			printf("read %s with %d labels\n", file, j);		
		}
	}
	
	if (this->dominator_set.size() == 0) {
	    FILE *dominators = fopen(DOMINATORS, "r");
	    if (dominators )
	    {
	        while (!feof(dominators))
	        {
	            fscanf(dominators, "%d", &v);
	            this->dominator_set.insert(v);
	        }
	        fclose(dominators);
	        printf("read %s with %d dominators\n", DOMINATORS, dominator_set.size() );
	    }
	}

	if (this->doomed_set.size() == 0) {
	    FILE *doomed = fopen(DOOMED, "r");
	    if (doomed) {
	        while (!feof(doomed))
	        {
	            fscanf(doomed, "%d", &v);
	            this->doomed_set.insert(v);
	        }
	        fclose(doomed);
	        printf("read %s with %d doomed\n", DOOMED, doomed_set.size() );
	    }
	}
	
	if (this->dominating_edges_set.size() == 0) {
	    FILE *dominating_edges = fopen(DOMINATING_EDGES, "r");
	    if (dominating_edges) {
	        while (!feof(dominating_edges ))
	        {
	            if (fscanf(dominating_edges , "%d", &v) != 1) continue;
	            this->dominating_edges_set.insert(v);
	        }
	        fclose(dominating_edges);
	        printf("read %s with %d dominating edges \n", DOMINATING_EDGES, dominating_edges_set.size() );
	    }
	}
	
}

void finite_automaton::clear_sinks() { //~MDC
      
	this->sinks_set.clear();
 
}

char* finite_automaton::transition_to_label(int t) { //~MDC
		
	return this->label[t];

}

int finite_automaton::index_of_label(char* letter) {
	
	for ( int i = 0; i < this->input_alphabet_size; i++) {
		
		if ( strcmp(label[i], letter) == 0) return i;
	}
	return -1;
	
}

bool finite_automaton::contains(const list<int> & word) const
{{{
	if(!this->valid)
		return false;

	set<int> current_states;
	set<int>::const_iterator si;

	current_states = this->initial_states;
	run(current_states, word.begin(), word.end());

	// check if a final state was reached
	map<int, bool>::const_iterator fi;
	for(si = current_states.begin(); si != current_states.end(); ++si) {
		fi = this->output_mapping.find(*si);
		if(fi != this->output_mapping.end()) {
			if(fi->second)
				return true;
		}
	}

	return false;
}}}
void finite_automaton::get_final_states(set<int> & into) const
{{{
	map<int, bool>::const_iterator oi;

	into.clear();

	for(oi = output_mapping.begin(); oi != output_mapping.end(); ++oi)
		if(oi->second)
			into.insert(oi->first);
}}}
set<int> finite_automaton::get_final_states() const
{{{
	set<int> final_states;
	this->get_final_states(final_states);
	return final_states;
}}}
void finite_automaton::set_final_states(const set<int> &final)
{{{
	set<int>::const_iterator si;
	this->set_all_non_accepting();
	for(si = final.begin(); si != final.end(); ++si)
		this->output_mapping[*si] = true;
}}}

void finite_automaton::set_all_non_accepting()
{{{
	this->output_mapping.clear();
	for(int i = 0; i < this->state_count; ++i)
		output_mapping[i] = false;
}}}

void finite_automaton::invert_accepting() // ~MDC
{{{
	for(int i = 0; i < this->state_count; ++i)
		output_mapping[i] = !output_mapping[i];
}}}
bool finite_automaton::parse_transition(string single)
{{{
	string tok;
	size_t p;
	char *endptr;

	int src, label, dst;

	// FROM
	p = single.find_first_of(',');
	tok = single.substr(0,p);
	if(p == string::npos)
		return false;
	single = single.substr(p+1, string::npos);

	src = strtol(tok.c_str(), &endptr, 10);
	if(*endptr)
		return false;

	// LABEL
	p = single.find_first_of(',');
	tok = single.substr(0,p);
	if(p == string::npos)
		return false;
	single = single.substr(p+1, string::npos);

	label = strtol(tok.c_str(), &endptr, 10);
	if(*endptr)
		return false;

	// TO
	tok = single;

	dst = strtol(tok.c_str(), &endptr, 10);
	if(*endptr)
		return false;

	this->transitions[src][label].insert(dst);

	return true;
}}}




basic_string<int32_t> simple_mVCA::serialize() const
{{{
	basic_string<int32_t> ret;

	if(!valid) return ret;

	ret += 0; // size, filled in later.

	ret += htonl(is_deterministic ? 1 : 2);
	ret += ::serialize(this->state_count);
	// alphabet
	ret += ::serialize(this->input_alphabet_size);
	ret += ::serialize(alphabet_directions);
	// end of alphabet
	ret += ::serialize(this->initial_states);
	set<int> final_states;
	this->get_final_states(final_states);
	ret += ::serialize(final_states);
	ret += ::serialize(m_bound);
	// transition function
	if(is_deterministic) {
		map<int, map<int, map<int, int> > > deterministic_transitions;
		map<int, map<int, map<int, set<int> > > >::const_iterator mmmsi;
		map<int, map<int, set<int> > >::const_iterator mmsi;
		map<int, set<int> >::const_iterator msi;
		set<int>::const_iterator si;
		for(mmmsi = transitions.begin(); mmmsi != transitions.end(); ++mmmsi)
			for(mmsi = mmmsi->second.begin(); mmsi != mmmsi->second.end(); ++mmsi)
				for(msi = mmsi->second.begin(); msi != mmsi->second.end(); ++msi) {
					bool found_one = false;
					for(si = msi->second.begin(); si != msi->second.end(); ++si) {
						if(found_one) {
							ret.clear();
							return ret;
						} else {
							found_one = true;
							deterministic_transitions[mmmsi->first][mmsi->first][msi->first] = *si;
						}
					}
				}
		ret += ::serialize(deterministic_transitions);
	} else {
		ret += ::serialize(transitions);
	}

	ret[0] = htonl(ret.length() - 1);

	return ret;
}}}
bool simple_mVCA::deserialize(serial_stretch & serial)
{{{
	int size;
	int type;

	set<int> final_states;
	set<int>::const_iterator si;

	map<int, map<int, map<int, int> > > deterministic_transitions;
	map<int, map<int, map<int, int > > >::iterator mmmi;
	map<int, map<int, int > >::iterator mmi;
	map<int, int >::iterator mi;

	if(!::deserialize(size, serial)) goto fail;
	if(size < 1) goto fail;
	if(!::deserialize(type, serial)) goto fail;
	switch(type) {
		case 1:
			is_deterministic = true;
			break;
		case 2:
			is_deterministic = false;
			break;
		default:
			goto fail;
	}
	if(!::deserialize(this->state_count, serial)) goto fail;
	for(int i = 0; i < this->state_count; ++i)
		this->output_mapping[i] = false;
	if(!::deserialize(this->input_alphabet_size, serial)) goto fail;
	if(!::deserialize(alphabet_directions, serial)) goto fail;
	if(!::deserialize(this->initial_states, serial)) goto fail;
	if(!::deserialize(final_states, serial)) goto fail;
	for(si = final_states.begin(); si != final_states.end(); ++si)
		this->output_mapping[*si] = true;
	if(!::deserialize(m_bound, serial)) goto fail;

	if(is_deterministic) {
		transitions.clear();

		if(!::deserialize(deterministic_transitions, serial)) goto fail;

		for(mmmi = deterministic_transitions.begin(); mmmi != deterministic_transitions.end(); ++mmmi)
			for(mmi = mmmi->second.begin(); mmi != mmmi->second.end(); ++mmi)
				for(mi = mmi->second.begin(); mi != mmi->second.end(); ++mi)
					transitions[mmmi->first][mmi->first][mi->first].insert(mi->second);
	} else {
		if(!::deserialize(transitions, serial)) goto fail;
	}

	return true;
fail:
	clear();
	return false;
}}}
string simple_mVCA::write() const
{
	// TODO
	return "simple_mVCA::write(): TODO.";
}
bool simple_mVCA::read(string input)
{
	// TODO
	return false;
}
string simple_mVCA::visualize() const
{
	// TODO
	return "simple_mVCA::visualize(): TODO.\n";
}

void simple_mVCA::get_final_states(set<int> & into) const
{{{
	map<int, bool>::const_iterator oi;

	into.clear();

	for(oi = output_mapping.begin(); oi != output_mapping.end(); ++oi)
		if(oi->second)
			into.insert(oi->first);
}}}
set<int> simple_mVCA::get_final_states() const
{{{
	set<int> final_states;
	this->get_final_states(final_states);
	return final_states;
}}}
void simple_mVCA::set_final_states(const set<int> &final)
{{{
	set<int>::const_iterator si;
	this->set_all_non_accepting();
	for(si = final.begin(); si != final.end(); ++si)
		this->output_mapping[*si] = true;
}}}
void simple_mVCA::set_all_non_accepting()
{{{
	this->output_mapping.clear();
	for(int i = 0; i < this->state_count; ++i)
		output_mapping[i] = false;
}}}



void bounded_simple_mVCA::clear()
{{{
	finite_automaton::clear();
	m_bound = 0;
}}}
bool bounded_simple_mVCA::calc_validity()
{{{
	if(!finite_automaton::calc_validity())
		goto invalid;

	if(m_bound < 0)
		goto invalid;

	return true;

invalid:
	this->valid = false;
	return false;
}}}
basic_string<int32_t> bounded_simple_mVCA::serialize() const
{{{
	basic_string<int32_t> ret;

	if(valid) {
		ret += 0;
		ret += finite_automaton::serialize();
		ret += ::serialize(m_bound);
		ret[0] = htonl(ret.length() - 1);
	}

	return ret;
}}}
bool bounded_simple_mVCA::deserialize(serial_stretch & serial)
{{{
	int size;

	clear();
	if(!::deserialize(size, serial)) goto failed;
	if(!finite_automaton::deserialize(serial)) goto failed;
	if(!::deserialize(m_bound, serial)) goto failed;

	this->valid = true;
	return true;
failed:
	clear();
	return false;
}}}
string bounded_simple_mVCA::write() const
{
	// TODO
	return "bounded_simple_mVCA::write(): TODO.";
}
bool bounded_simple_mVCA::read(string input)
{
	// TODO
	return false;
}
string bounded_simple_mVCA::visualize() const
{
	// TODO: add label with m_bound.
	return finite_automaton::visualize();
}



} // enf of namespace libalf.


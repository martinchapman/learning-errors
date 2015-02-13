#include <iostream> 
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// Used to define the libalf name space.
#include <libalf/alf.h>
// Angluin's L* algorithm
#include <libalf/algorithm_angluin.h>
#include <vector>
#include <map>
#include <ctime>
#include "../../file_names.h" // ofer
#ifdef _EXPERIMENT_MODE
#include <boost/unordered_map.hpp>
#endif

int Assert_letter;
using namespace std;
using namespace libalf;
int alphabet_size; 
int min_func_idx; // index of first function
bool instrument_branches = false, instrument_functions = false;
int mem_queries, conjectures, cbmc_mem_queries, cfg_queries, cfg_prefix;
int feedback = -1;

void predecessors(int m, int current, int *predecessors_list);
void instrument();
void Abort(string msg);
void exitLearn();
int run(const char* cmd);
bool verbose = false;

struct myEdge {char s[100]; char t[100];};

map<int, string> func_name; // maps index to a function name

string 
	input_file_name_full,		// original full path (path/file.c => path/file.c)
	input_file_prefix,			// path/file.c =>  _file 
	input_file_exe,				// path/file.c => <input_file_prefix>.exe
	input_file_seq,				// path/file.c => <input_file_prefix>.seq
	input_file_is, 				// path/file.c => <input_file_prefix>.is
	input_file_working_copy,	// path/file.c => <input_file_prefix>.c	
    input_file_no_extention;	// path/file.c => path/file

unsigned word_length, unwind = 0; 
// ~MDC 'User bound'
ostringstream unwind_s;
ostringstream unwind_setlimit;

// CBMC membership query cache
#ifdef _EXPERIMENT_MODE
boost::unordered_map<std::list<int>, bool> MEMBERSHIP_QUERY_CACHE;

enum membership_query_cache_resultt {
  IN_LANGUAGE,
  NOT_IN_LANGUAGE,
  NO_ENTRY_FOUND
};

membership_query_cache_resultt lookup_query(const std::list<int> &query) {
  const typeof(MEMBERSHIP_QUERY_CACHE.begin()) it(MEMBERSHIP_QUERY_CACHE.find(query));
  if(MEMBERSHIP_QUERY_CACHE.end() == it) { return NO_ENTRY_FOUND; }
  return it->second ? IN_LANGUAGE : NOT_IN_LANGUAGE;
}

void remember_query(const std::list<int> &query, bool result) { MEMBERSHIP_QUERY_CACHE.insert(std::make_pair(query, result)); }
#endif

//~MDC Needs to be addressed
void rewrite_branch( string name, int num) 
{

}

// we duplicate file.f to file.is ("interesting set") where the latter has "c::" prefix before each function name, because 
// 1) we want the user to enter natural names, 
// 2) goto-instrument must have the c:: prefix, 
// 3) func_names is produced by another tool that also generates natural names. So some conversion is necessary in any case. 
void create_interesting_set(FILE *f) {
	char name[100];
	string st = "rm " + input_file_is;
	run(st.c_str()); // remove old .is file, even if we do not create a new one. 
	FILE *func_names_for_goto_inst = fopen(input_file_is.c_str(), "w");  // we duplicate file.f to file.is where the latter has "c::" prefix before each function name, because 1) we want the user to enter natural names, 2) goto-instrument must have the c:: prefix, 3) func_names is produced by another tool that also generates natural names. So some conversion is necessary in any case. 
	while (!feof(f)) {
		if (fscanf(f, "%s", name) != 1) continue;		
		fprintf(func_names_for_goto_inst, "%s\n", name);
    //fprintf(func_names_for_goto_inst, "c::%s\n", name);
	}
	fclose(func_names_for_goto_inst);
}

int generate_func_names(int letter) {

	stringstream tmp;
    
    // ~MDC Convert .c source into 'master' object file
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-cl -c " << input_file_working_copy << " /Fo" << input_file_exe << "\"";
#else
    "goto-cc -c " << input_file_working_copy << " -o " << input_file_exe;
#endif
    
    run(tmp.str().c_str());
    
    stringstream st, st1;
    st << input_file_no_extention << ".f";
    FILE *user_func_names = fopen(st.str().c_str() , "r");
    
    if (user_func_names == NULL) {
        
        // ~MDC Using new learn feature of goto-instrument, internally instrument functions for learn processing. Also outputs func_names.data
        tmp.str("");
        tmp <<
#ifdef _MYWIN32
        "cmd /c \"goto-instrument --learn " << input_file_exe << " " << input_file_exe << "\"";
#else
        "goto-instrument --learn " << input_file_exe << " " << input_file_exe;
#endif
        
        run(tmp.str().c_str());
        
    } else {
        
        // ~MDC Same as instrumentation above, except here we restrict the functions instrumented to a subset specified in an external file 
        tmp.str("");
        tmp <<
#ifdef _MYWIN32
        "cmd /c \"goto-instrument --learn --learn-functions " << input_file_no_extention << ".f" << " " << input_file_exe << " " << input_file_exe << "\"";
#else
        "goto-instrument --learn --learn-functions " << input_file_no_extention << ".f" << " " << input_file_exe << " " << input_file_exe;
#endif
        
        run(tmp.str().c_str());
        
    }

    // ~MDC Manually add main for consistency with original version, may not be necessary.
	FILE *func_names2 = fopen(FUNC_NAMES, "a");
	fprintf(func_names2, "%s\n", "main");
	fclose(func_names2);

    // reads func names from FUNC_NAMES and
    // 1) fills the global list node_index (to be used later in compute_allowed_pairs())
    // 2) populates AUTO_LABELS_FUNCTIONS with function labels,
    // 3) prepares the CONVERT (convert.bat) file, which removes calls to _Learn_func_enter that we are not interested in (e.g. 'main, check_conjecture, etc),
    //    and replaces the (char *) <func_name> with (int index) in the file a.c (the result of goto-instrument). Using int rather than strings avoids
    //    strcmp() instructions which turn into loops by cbmc. (~MDC Depreciated)
    char name[100];
    map<string, int> user_func_set;
    FILE *func_names = fopen(FUNC_NAMES, "r"),
    *Labels = fopen(AUTO_LABELS_FUNCTIONS, "w");
    
    if (func_names == NULL) Abort(string("cannot open ") + string(FUNC_NAMES));
    
    if (user_func_names == NULL) cout << "Using all function names (other than 'main'). A restricted list can be given in a file " << input_file_no_extention << ".f" << endl;
    
    create_interesting_set(func_names);
    rewind(func_names);
    
    while (!feof(func_names)) {
        if (fscanf(func_names, "%s", name) != 1) continue;
        if (!strcmp(name, "main")) // here we can add other functions we wish to ignore
        {
            cout << "skipping " << name << endl;
            continue;
        }
        
        func_name.insert(pair<int, string>(letter, string(name)));
        fprintf(Labels, "%d %s\n", letter, name);
        // ~MDC Manually increment letter
        letter++;
    }
	// what's special about assert is that it is not instrumented, being a library function. Inside Learn_assert we invoke Learn(alphabet-1)

	fprintf(Labels, "%d %s\n", letter, "Learn_Assert"); // changed from assert

	func_name.insert(pair<int, string>(letter++, string("Learn_Assert")));	// changed from assert
	func_name.insert(pair<int, string>(letter++, string("main")));	// we force main to be at index m + 1 for convenience when building matrix later on. It will not be part of the alphabet (see line).

	fclose(func_names);
	fclose(Labels);	
	return letter - 1; // '-1' because this number is fed into alphabet_size, and we do not want main to be part of the alphabet.
}

void Abort(string msg) {
	cerr << msg << endl;
	exit(1);
}

/****************************** before learn *************************/


void define_file_prefixes(string file_name)
{
	input_file_name_full = file_name;
	FILE *in;
	if ((in = fopen(input_file_name_full.c_str(),"r")) == NULL) Abort(string("file ") + input_file_name_full + string("cannot be opened"));
	fclose(in);
	assert(input_file_name_full[input_file_name_full.size() - 2]=='.');

	string 
		input_file_name_base, // path/file.c => file
		input_file_path; // path/file.c => path
	int len = input_file_name_full.length();	
	int i;
	for (i = len - 1; i >= 0; --i) {		
		if (input_file_name_full[i] == '/') break;		
	}

	input_file_name_base = input_file_name_full.substr(i + 1);
	input_file_path = input_file_name_full.substr(0,i + 1);
	cout << "base = " << input_file_name_base << " path = " << input_file_path << endl;

	string base_without_extension = input_file_name_base.substr(0,input_file_name_base.size() - 2);
	input_file_prefix		= "_" + base_without_extension;
	input_file_working_copy = input_file_prefix + ".c";
#ifdef _MYWIN32	
	input_file_exe			= input_file_prefix + ".exe";		
#else
	input_file_exe			= input_file_prefix + ".o";		
#endif	
	input_file_seq			= input_file_prefix + ".seq"; // we rely on the ".seq" extension later so do not change it. 		
	input_file_is			= input_file_prefix + ".is";		
	input_file_no_extention = input_file_path + base_without_extension;	
    
}

void parse_options(int argc, const char**argv) {		

	if (argc < 3) Abort(string(
		"Usage: online <file_name> <word-length> [--auto {b,f}]* [--v] [--unwind #] [<user (manualy inserted) alphabet-size>]\n\n" 
		"file_name can contain a unix-style path. \n"
		"\t -- auto\tautomatic instrumentation of (f)unction entries or (b)ranch.\n"
		"\t\t\t if (f) is chosen, each function becomes a letter in the alphabet. Ignores alphabet-size if given. \n"
		"\t --v: \tverbose.\n"
		"\t --unwind <k>: \tcbmc's unwinding = max(k, alphabet-size+1).\n"
		"\t Default 'manual' alphabet-size is 0.\n"
));
		
	define_file_prefixes(argv[1]);
     
    word_length = atoi(argv[2]);
    
    unwind_s << 1;
    
	for (int i = 3; i < argc ; ++i) {
		if (!strcmp(argv[i], "--auto")) {
			if (argc == i + 1) Abort("missing argument {'b','f'}  for --auto\n"); 
			if (!strcmp(argv[i+1], "b")) instrument_branches = true;
			else if (!strcmp(argv[i+1], "f")) instrument_functions = true;
			else Abort("argument after --auto must be in {'b','f'}");
			++i;
		}
		else if (isdigit(argv[i][0])) alphabet_size = atoi(argv[3]); 
		else if (!strcmp(argv[i], "--v")) verbose = true;
        // ~MDC Can supply own 'user loop' bound, otherwise defaults to 1
        else if (!strcmp(argv[i], "--user-unwind")) { unwind_s.str(""); unwind_s << argv[i+1]; }
		else if (!strcmp(argv[i], "--unwind")) {
			++i;
			if (argc == i || !isdigit(argv[i][0])) Abort("missing number after --unwind\n"); 
			unwind = atoi(argv[i]);
		}
		else Abort(string("wrong argument: ") + string(argv[i]));
	}	
    
	if (alphabet_size == 0 && !instrument_branches && !instrument_functions) Abort("alphabet size must be > 0, or --auto should be used.");
}

void remove_files() {
    #ifdef _EXPERIMENT_MODE
        ostringstream tmp;
        tmp << "rm -f " << AUTO_LABELS;
        run(tmp.str().c_str());
    #else
        ostringstream tmp;
        tmp << "rm -f " << AUTO_LABELS << " " << POSITIVE_QUERIES_FILE << "; echo > " << POSITIVE_QUERIES_FILE;	// we need a positives_query file because it is included from other files.
        run(tmp.str().c_str());
    #endif
}


void preprocess_source() {	
	// adding 'include "learn.c" ' in the first line of the source file. It is necessary for goto-cl because of the Learn_Assert command. 
	stringstream tmp;
    
	tmp << 
#ifdef _MYWIN32
	  "cmd /c " <<
          "sed -e '1i\\#include \\\"learn.c\\\"' " << input_file_name_full << " > "  << input_file_working_copy;
#else
          "sed -e \"1i\\\\\n\\#include \\\"learn.c\\\"\" " << input_file_name_full << " > " <<  input_file_working_copy; 
#endif

	run(tmp.str().c_str());	
	/*tmp.str("");		
	tmp << "cp tmp " << input_file_working_copy;
	run(tmp.str().c_str());	*/
}

void init_auto_instrumentation()
{
    stringstream tmp;
    
    if (instrument_branches) {
        alphabet_size += 2;		
        rewrite_branch("not-taken", 0);
        rewrite_branch("taken", 1);
    }
    if (instrument_functions) {
    
        min_func_idx = alphabet_size;
        
        alphabet_size = generate_func_names(alphabet_size); // this one also updates AUTO_LABELS_FUNCTIONS		
    }	
    else {
        alphabet_size++; // because of the assert function.	If instrument_function is true, it updates it anyway.
        min_func_idx = alphabet_size; // we need to define it because it is used in answer_query
    }
    
    if (instrument_branches || instrument_functions) {
        tmp.str("");
        tmp << "cat " << (instrument_branches ? AUTO_LABELS_BRANCHES : " ") << " " << (instrument_functions ? AUTO_LABELS_FUNCTIONS : " ") << " > " << AUTO_LABELS;
        run(tmp.str().c_str());
        
    }
    Assert_letter = alphabet_size - 1; // not suppose to change alphabet_size from this point on.
}

void init_word_length_file() {
	printf("reading from %s; word_length = %d, alphabet-size = %d\n", input_file_working_copy.c_str(), word_length, alphabet_size);
	FILE *file = fopen(WORD_LENGTH, "w");
	fprintf(file, "#define word_length_bound %d\n", word_length);
	fprintf(file, "#define AlphaBetSize %d", alphabet_size);
	fclose(file);	
    
    unwind_setlimit << max(word_length + 1, unwind); // we need to unroll one more than the word_length
}



/******************************* after learn *************************/

void post_process() {
	
#ifdef _MYWIN32
  run("cmd /C \"dominators.exe\"");
  run("cmd /C \"dfs.exe\"");
#else
  run("./dominators");
  run("./dfs");
#endif	
}

void show_result(conjecture *result) {	
	finite_automaton * a = dynamic_cast<finite_automaton*> (result);
	streambuf* strm_buffer = cout.rdbuf();		// redirecting cout to a.out. We need this because visualize() returns an ostream.
	ofstream dot("a.dot");
	cout.rdbuf (dot.rdbuf());	
	cout << a->visualize();
	dot.close();
	cout.rdbuf (strm_buffer); 

    // Temporarily disabled immediate visual feedback of automaton.
	//run("dotty a.dot");	
}

/*******************************  Learn  ****************************/
list<int> get_CounterExample(int alphabetsize, int *feedback) {
    
	list<int> ce;
	int  i;
	int length;
	ifstream read(MODEL);
	read >> *feedback;

	assert(*feedback == 0 || *feedback == 1);
	cout << ((*feedback) ? "Positive " : "Negative ") << "feedback" << endl;
	cout << "Counterexample ";
	read >> length;
	cout << "(length = " << length << ")";
	
	while((length--) && read>>i ) 
	{
		cout << " read: " << i;
		ce.push_back(i);		
	}
	cout << endl;
    
	return ce;
}

int run(const char* cmd) {	
	int res;
	if (verbose) {cout << endl << "---------- external command -----------" << endl << cmd << endl;}
	res = system(cmd);
	if (verbose) {cout << endl << "---------------------------------------" << endl;}
	cout.flush();
	return res;
}

int run_cbmc(bool membership) {
	stringstream tmp;	
	string tmp_file("tmpfile");
	tmp << "echo \"#define " << (membership ? "membership" : "conjecture") << "\" > " << MODE;
	run(tmp.str().c_str());
    
    // ~MDC Convert learn code per run of cbmc to account for changes
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-cl -c learn_code.c /Folearn_code.o \"";
#else
    "goto-cc -c learn_code.c -o learn_code.o";
#endif
    
    run(tmp.str().c_str());
    
    // ~MDC Combine learn code object with target code object
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-cl " << input_file_exe << " learn_code.o /Fe" << "learn" << input_file_exe << "\"";
#else
    "goto-cc " << input_file_exe << " learn_code.o -o " << "learn" << input_file_exe;
#endif
    
    run(tmp.str().c_str());
    
    // ~MDC Run combined objects through CBMC
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"" <<
#endif
    "cbmc -Iansi-c-lib --unwind " << unwind_s.str() << " --unwindset Learn_trap.0:" << unwind_setlimit.str() << ",check_conjecture.0:" << unwind_setlimit.str() << ",check_conjecture_at_trap.0:" << unwind_setlimit.str() << " --no-unwinding-assertions --xml-ui " << "learn" << input_file_exe << " > " <<
    tmp_file
    
#ifdef _MYWIN32
    << "\""
#endif
    ;
    
	run(tmp.str().c_str());
	tmp.str("");

	tmp << "grep ERROR " << tmp_file;
	if (!run(tmp.str().c_str())) Abort(string("ERROR in output of CBMC (see " + tmp_file = ")"));
		
	if (!membership) { // in case of conjecture query, we extract the counterexample
		string cmd = 
#ifdef _MYWIN32
		  string("cmd /c ") + string("\"") + CE + string(" ") + tmp_file + "\"";
#else
                  CE + string(" ") + tmp_file;
#endif
		run(cmd.c_str());		
	}
	tmp.str("");
	tmp <<  "grep -q FAILURE " << tmp_file;
	int res = run(tmp.str().c_str());
	if (res == 0) return 0;
	
	tmp.str("");
	tmp <<  "grep -q SUCCESS " << tmp_file;
	res = run(tmp.str().c_str());
	if (res == 0) return 1;
	Abort("CBMC FAILURE");	
        return 0; //unreachable
}

bool answer_Conjecture(conjecture * cj) {

	assert(cj != NULL);
    
    conjectures++;

	finite_automaton * a = dynamic_cast<finite_automaton*> (cj);
	cout << endl << "Conjecture:" << endl << endl;
	cout << a->visualize();
	streambuf* strm_buffer = cout.rdbuf();		// redirecting cout to a.out. We need this because visualize() returns an ostream.
	// ~MDC Temporary disable of visualising intermediate conjectures
    //ofstream dot("a.dot");
	//cout.rdbuf (dot.rdbuf());
	//cout << a->visualize();
	//dot.close();

	ofstream candidate(CONJECTURE_DATA);    // same thing for write()
	cout.rdbuf (candidate.rdbuf());
	cout << a->write(); // write() is a rewrite of the original lib function. 
	candidate.close();
	cout.rdbuf (strm_buffer); // reverting cout to its normal behavior. 			
	int res = run_cbmc(false);	
	cout << " " << (res != 0 ? "(yes - equivalent)" : "(no - not equivalent)") << endl;		
	return (res != 0);	
}

void positive_queries(list<int> query) {
	list<int>::iterator it;
	unsigned size = query.size();		
	ostringstream ist;		
	ist << "echo \"if (_Learn_idx == " << size << " && ";
	int i = 0;
	for (it = query.begin(); it != query.end(); ++i)			
	{
		ist << "_Learn_b[" << i  << "] == " << *it;			
		it++;
		if (it != query.end()) ist << " && "; else ist << ") __CPROVER_assume (0); \" >> " << POSITIVE_QUERIES_FILE;			
	}
	run (ist.str().c_str());
}

// returns: 0 = reject, 1 = accept, 2 = don't know. 
char membership_pre_checks(list<int> query) {
	
	// empty query
	
	if (query.size() == 0) 
	{
		cout << "Zero-size!" << endl;
		return 0;
	}
 
  if (query.size() > word_length)
  {
    cout << "Word too long!" << endl;
    return 0;
  }
	
	// The query is right after conjecture. We know the answer anyway. We use it only if it is positive feedback. If it is negative feedback we recheck anyway.
	// The difference between positive and negative feedback is emenating from how we catch negative feedbacks. We do so by the 'trap', which extends any path reaching the end with an arbitrary sequence. 
	// if that sequence happens to drive us to an accepting state in the current conjecture, we conclude that this is a negative feedback. But there can be a different input that creates exactly the same path
	// and indeed violates the assertion. So we query the counterexample, to see if it happens to be positive.
	if (feedback == 1)
	{
		positive_queries(query);
		cout << "Feedback from conjecture!" << endl;
		feedback = -1;
		return 1;
	}
	

	// query longer than word_length. It will be rejected anyway. 
	//if (query.size() > word_length) 
	//{
	//	cout << "Long!" << endl;
	//	return 0;
	//}
	
	// last letter must be 'assert' 
	list<int>::reverse_iterator rit = query.rbegin();
	if (*rit != Assert_letter) {		
		cout << "End!" << endl;
		return 0;
	}

	// only last letter can be 'assert' . 
	// Note that the assert can be inside a loop, and call it several times before it fails it.  Nevertheless in learn_code.c/Learn_Assert(b)
	// we make sure that the assert letter is reported only if the assert condition is false. And this can only happen in the 
	// end of the execution.
	int size = query.size() - 1;
	for (list<int>::iterator it = query.begin(); size; it++, size--) 
	{	
		if (*it == Assert_letter) {		
			cout << "assert before end! \n"; 
			return 0;
		}
	}

	return 2;
}

bool membership_cfg_checks(list<int> query) {
	static list<int> bad_prefix(1,-1);	
	static int failure_point = -1;
	list<int>::iterator it;
	stringstream st;	
	bool same_prefix = true;
	list<int>::iterator bad_prefix_it = bad_prefix.begin();
	for (it = query.begin(); it != query.end(); ++it) 
		if (*it >= min_func_idx) 
		{
			if (same_prefix && failure_point >=0 ) {
				if (bad_prefix_it == bad_prefix.end()) {  // same prefix as the previous failed one; we skip cfg check and return false. 
					cout << "cfg (prefix)" << endl; 
					++cfg_prefix; 
					return false;
				}
				if (*bad_prefix_it != *it) same_prefix = false;
				++bad_prefix_it;
			}
			st << func_name[*it] << endl;
      //st << "c::" << func_name[*it] << endl;
		}
		stringstream tmp;		
		FILE *seq = fopen(input_file_seq.c_str(), "w");
		fprintf(seq, "main\n%s", st.str().c_str()); // we add main because 1) it is not in the alphabet, but 2) it is necessary for identifying the sequence in the cfg by goto-instrument
    //fprintf(seq, "c::main\n%s", st.str().c_str()); // we add main because 1) it is not in the alphabet, but 2) it is necessary for identifying the sequence in the cfg by goto-instrument
		fclose(seq);
    
#ifdef _MYWIN32
    // ~MDC grep search for 'not feasible' may need altering
    tmp << "cmd /c " <<  "\"goto-instrument " << input_file_exe << " --check-call-sequence " << input_file_prefix << " --call-sequence-bound 35 | tee tmp1 | grep -c \"not feasible\" > _seq.res\"";
    // TODO: change '35' to something more proportional to the word-length. It prevents observing sequence of non-interesting function of length > 35, which is important for preventing non-termination when there is recursion of such functions.
#else
    tmp <<				   "goto-instrument " << input_file_exe << " --check-call-sequence " << input_file_prefix << " --call-sequence-bound 35 | tee tmp1 | grep -c \"not feasible\" > _seq.res";
    // TODO: change '35' to something more proportional to the word-length. It prevents observing sequence of non-interesting function of length > 35, which is important for preventing non-termination when there is recursion of such functions.
#endif

		run(tmp.str().c_str());
		++cfg_queries;
		FILE *seq_res = fopen ("_seq.res", "r");
		int res;
		if (fscanf(seq_res, "%d", &res) != 1) Abort("cannot read _seq.res");
		fclose(seq_res);	
        //cout << res << endl;
        //exit(1);
		if (res == 1) {
			cout << "cfg! "; 
			// now we find where the point of failure was
			tmp.str("");
			tmp << "tail -n 1 tmp1 > _seq_failure.res";
			run(tmp.str().c_str());
			seq_res = fopen ("_seq_failure.res", "r");
			if (fscanf(seq_res, "%d", &failure_point) != 1) Abort("cannot read _seq_failure.res");
      fclose(seq_res);
			bad_prefix.clear();
			list<int>::iterator tmp_it = query.begin();
			cout << "bad prefix = ";
			for (int i = 0; i < failure_point; ++i) 
			{ 
				bad_prefix.push_back(*tmp_it);
				cout << *tmp_it << " ";
				++tmp_it;
			}
			cout << endl;
			return false;
		}
		return true;
}

bool answer_Membership(list<int> query) {
	
	list<int>::iterator it;
	stringstream st;	

	mem_queries++;
	cout << "Please classify the word: ";	
	for (it = query.begin(); it != query.end(); ++it ) cout << ' ' << *it;
	cout << " ";
	
	// cheap pre-checks
	char pre_res = membership_pre_checks(query);  // 0 - false, 1 - true, 2 - no finding
	 if (pre_res != 2) return (bool) pre_res; 

#ifdef _EXPERIMENT_MODE
  const membership_query_cache_resultt cached_result(lookup_query(query));
  if(NO_ENTRY_FOUND != cached_result) {
    cout << "Cached membership query!" << endl;
    return IN_LANGUAGE == cached_result;
  }
#endif

	// if instrumenting function calls, word has to be compatible with the cfg
	if (instrument_functions && !membership_cfg_checks(query)) {
#ifdef _EXPERIMENT_MODE
    //remember_query(query, false);
#endif
    return false;
  }
		
	cout.flush();
	// all pre-tests failed. Going into a cbmc call.

	bool saw_assert_test_letter = false;
	
	cout << " | ";
	st << "#include \"" << MEMBERSHIP_DATA_H << "\"\n"	<< "\nint _Learn_mq[mq_length] = {";
	for (it = query.begin(); it != query.end(); )
	{		
		
		if (!instrument_functions) 
		{	// cannot have two 'asserts' in the word
			if (*it == Assert_letter) {
				if (saw_assert_test_letter) {cout << *it << " ! \n"; return false;}
				saw_assert_test_letter = true;				
			}
		}
		cout << *it;
		st << *it;
		it++;
		if (it != query.end()) st << ", ";
	}
	st << "};";
	cbmc_mem_queries++;
	FILE *file = fopen(MEMBERSHIP_DATA, "w");
	fprintf(file, "%s", st.str().c_str());
	fclose(file);

	st.str("");
	file = fopen(MEMBERSHIP_DATA_H, "w");
	st << "#define mq_length " << query.size() << "\nextern int _Learn_mq[mq_length];";
	fprintf(file, "%s", st.str().c_str());
	fclose(file);
	

	cout << endl;

	fflush(stdout);
	
	const int res = run_cbmc(true);
  const bool cbmc_result = res == 0;
#ifdef _EXPERIMENT_MODE
  if(cbmc_result) { /*remember_query(query, cbmc_result);*/ }
#endif	
	
	cout << " " << (cbmc_result ? "(yes)" : "(no)") << endl;
	
	// updating the positive_queries_file: this will block paths that correspond to membership that we already answered positively.
	if (cbmc_result) positive_queries(query);

	return cbmc_result;	
}

void learn() {
	// Create new knowledge-base. In this case, we choose bool as type for the knowledge-base.
	knowledgebase<bool> base;
	conjecture *result = NULL;	

	// Create learning algorithm (Angluin L*) without a logger (2nd argument is NULL) and alphabet size alphabet_size
	angluin_simple_table<bool> algorithm(&base, NULL, alphabet_size);
		
	bool conjectured = false;
	int counter = 0;
	do {	
		// Advance the learning algorithm
		conjecture *cj = algorithm.advance();		
		// Resolve membership queries
		if (cj == NULL) {			
			//counter++;
			// retrieve queries
			list<list<int> > queries = base.get_queries();

			// iterate through all queries
			list<list<int> >::iterator li;
			for (li = queries.begin(); li != queries.end(); li++) {

				// Answer query				
				bool a = answer_Membership(*li);				

				// Add answer to knowledge-base
				base.add_knowledge(*li, a);
			}
						
		//	if (counter > 1 && conjectured) exit(1);
	//		if (conjectured) exit(1);
			conjectured = false;
		}
		// Resolve equivalence queries
		else {			
			counter++;
			if (conjectured) Abort(string("last counterexample corresponds to a nondeterministic path: it can either belong or not belong to the language. "));
			conjectured = true;
			bool is_equivalent = answer_Conjecture(cj);			
//			if (counter == 2) exit(1);
			if (is_equivalent) {
				result = cj;
			} else {
				// Get a counter-example
				//exit(1);
				list<int> ce = get_CounterExample(alphabet_size, &feedback);
				//++counter;
				//if (counter == 1) exit(1);
				
				// Add counter-example to algorithm
				algorithm.add_counterexample(ce);
				
				// Delete old conjecture
				delete cj;
			}
		}
		

	} while (result == NULL);
	
	post_process();
	
	show_result(result);	// we do it inside learn because result is a pointer to a local object. 
	
	delete result;	
}

void exitLearn() {
    
    string rm_input_file_exe = "rm " + input_file_exe;
    run(rm_input_file_exe.c_str());
    
    string rm_input_file_seq = "rm " + input_file_seq;
    run(rm_input_file_seq.c_str());
    
    string rm_input_file_is = "rm " + input_file_is;
    run(rm_input_file_is.c_str());
    
    string rm_input_file_working_copy = "rm " + input_file_working_copy;
    run(rm_input_file_working_copy.c_str());
    
}

#ifdef _EXPERIMENT_MODE
void reset(std::ostringstream &ss) {
  ss.clear();
  ss.str("");
}

void reset_global_variables() {
  reset(unwind_s);
  reset(unwind_setlimit);
  alphabet_size = 0;
}

void copy_file(const char *source, const char *destination) {
  std::ifstream  src(source, std::ios::binary);
  std::ofstream  dst(destination, std::ios::binary);
  dst << src.rdbuf();
}

int countNodes(const char* filename) {
    int nodes = 0;
    std::ifstream input(filename);
    std::string line;
    while( std::getline( input, line ) ) {
        if ( line.find("shape=circle") != std::string::npos || line.find("shape=doublecircle") != std::string::npos )
        nodes++;
    }
    return nodes;
}

int countEdges(const char* filename) {
    int edges = -1;
    std::ifstream input(filename);
    std::string line;
    while( std::getline( input, line ) ) {
        if ( line.find("->") != std::string::npos )
            edges++;
    }
    return edges;
}

bool hasBackedges(const char* filename) {
    std::ifstream input(filename);
    std::string line;
   
    while( std::getline( input, line ) ) {
        if ( line.find("q0 -> q0") != std::string::npos && line.find("blue") == std::string::npos ) {
            return true;
        }
    }
    return false;
}

bool hasLoops() {
    stringstream tmp;
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-instrument " << input_file_exe << " --show-loops " << input_file_exe << " | wc -l > _loops.res\"";
#else
    "goto-instrument " << input_file_exe << " --show-loops " << input_file_exe << " | wc -l > _loops.res";
#endif
    
    run(tmp.str().c_str());
    
    FILE *seq_res = fopen ("_loops.res", "r");
    int loops;
    if (fscanf(seq_res, "%d", &loops) != 1) Abort("cannot read _loops.res");
    fclose(seq_res);
    
    if (loops > 1)
        return true;
    
    return false;
}

bool testConvergence(int lowest_word_length, int word_length, int user_bound) {
    // ~MDC: Number of automata that must match to signal convergence 
    int NUMBER_MATCHING = 2;
    bool matching = false;
    if ( (word_length - lowest_word_length) >= NUMBER_MATCHING ) {
        matching = true;
        
        for ( int remove_length = lowest_word_length; remove_length < word_length - ( NUMBER_MATCHING - 1 ); remove_length++ ) {
            stringstream st;
            st << "rm " << " learn_output/" << input_file_prefix << "-" << user_bound << "-" << remove_length << ".dot";
            //run(st.str().c_str());
        }
        
        for ( int current_length = word_length - ( NUMBER_MATCHING - 1 ); current_length < word_length; current_length++ ) {
            std::stringstream file_a_path;
            file_a_path << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << (current_length - 1) << ".dot";
            std::stringstream file_b_path;
            file_b_path << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << current_length << ".dot";
            
            if (hasBackedges(file_a_path.str().c_str())) {
                matching = false;
                break;
            }
            
            if (hasBackedges(file_b_path.str().c_str())) {
                matching = false;
                break;
            }
            
            if (countNodes(file_a_path.str().c_str()) != countNodes(file_b_path.str().c_str()) || countEdges(file_a_path.str().c_str()) != countEdges(file_b_path.str().c_str())) {
                matching = false;
                break;
            }
        }
    }
    return matching;
}

#define WORD_LENGTH_ARGUMENT_INDEX 2
#define USER_BOUND_ARGUMENT_INDEX 7
#define LOG_EACH_LENGTH false
#endif

/*******************************  main  ****************************/
int main(int argc, const char**argv) {
    
#ifdef _EXPERIMENT_MODE
    
    for(int user_bound = 1; user_bound < 4; ++user_bound) {
        
#endif
        clock_t begin = clock();
        
#ifdef _EXPERIMENT_MODE
        
        // ~MDC initial value of word_length should be estimate of lower bound
        for(int word_length = 1; word_length < 50; ++word_length) {
            
            std::ostringstream ss;
            ss << user_bound;
            const std::string user_bound_argument(ss.str());
            argv[USER_BOUND_ARGUMENT_INDEX] = user_bound_argument.c_str();
            reset(ss);
            ss << word_length;
            const std::string word_length_argument(ss.str());
            argv[WORD_LENGTH_ARGUMENT_INDEX] = word_length_argument.c_str();
            reset_global_variables();
#endif
            
            parse_options(argc, argv);
            remove_files();
            preprocess_source();
            init_auto_instrumentation();
            init_word_length_file();
            
            learn();
            
#ifdef _EXPERIMENT_MODE
            reset(ss);
            ss << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length << ".dot";
            copy_file("a.dot", ss.str().c_str());
            // ~MDC Replace 1 with lower bound estimation
            if (testConvergence(1, word_length, user_bound) || LOG_EACH_LENGTH) {
                
#endif
                clock_t end = clock();
                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                cout << " membership queries: " << mem_queries << " (" << cbmc_mem_queries << " cbmc calls - " << (float)cbmc_mem_queries * 100/(float)mem_queries << "\%)" << " cfg queries: " << cfg_queries << " cfg queries (prefix): " << cfg_prefix << " total conjectures: " << conjectures << endl;
                cout << "Time: " << elapsed_secs << endl;
                
#ifdef _EXPERIMENT_MODE
                
                std::stringstream final_automaton_path;
                final_automaton_path << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length << ".dot";
                
                std::stringstream final_automaton_stats_filename;
                final_automaton_stats_filename << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length;
                
                ofstream final_automaton_stats_file;
                final_automaton_stats_file.open(final_automaton_stats_filename.str().c_str());
                
                std::stringstream final_automaton_stats_info;
                // Name, Nodes, Edges, Lower Bound, Convergence Bound, User Bound, Seconds gone, CBMC mem queries / total queries, Conjectures, Iterations
                final_automaton_stats_info << input_file_prefix << " & " << countNodes(final_automaton_path.str().c_str()) << " & " << countEdges(final_automaton_path.str().c_str()) << " & " << 1 << " & " << word_length << " & " << user_bound << " & " << elapsed_secs << " & " << (float)cbmc_mem_queries * 100/(float)mem_queries << " & " << conjectures << " & " << word_length - 1;
                
                final_automaton_stats_file << final_automaton_stats_info.str();
                final_automaton_stats_file.close();
                
                break;
                
            }
            
        }
        
        if ( !hasLoops() )
        break;
        
    }
    
#endif
    
    return 0;
    
}

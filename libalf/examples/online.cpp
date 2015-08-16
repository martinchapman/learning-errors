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
#include <libalf/algorithm_rivest_schapire.h>
#include <vector>
#include <map>
#include <ctime>
#include <ctype.h>
#include <unordered_set>
#include "../../file_names.h" // ofer
#include <boost/algorithm/string.hpp> // ~MDC
#include <boost/lexical_cast.hpp>
#ifdef _EXPERIMENT_MODE
#include <boost/unordered_map.hpp>
#endif

int Assert_letter;
using namespace std;
using namespace libalf;
int alphabet_size;
int min_func_idx; // index of first function
bool instrument_branches = false, instrument_functions = false;
int mem_queries, cbmc_conjectures, conjectures, cbmc_mem_queries, cache_mem_queries, cfg_queries, cfg_prefix;
enum {CONJ_FALSE, CONJ_TRUE, CONJ_UNKNOWN} conjecture_result = CONJ_UNKNOWN, prev_conjecture_result = CONJ_UNKNOWN;
enum {Learn_Angluin, Learn_RS} learning_alg = Learn_Angluin;
void Abort(string msg);
int run(const char* cmd);
bool verbose = false;
list<int> *CURRENT_QUERY = 0;
finite_automaton *CURRENT_CONJECTURE = 0;

map<int, string> func_name; // maps index to a function name

string
input_file_name_full,		// original full path (path/file.c => path/file.c)
input_file_prefix,			// path/file.c =>  _file
input_file_exe,				// path/file.c => <input_file_prefix>.exe
input_file_seq,				// path/file.c => <input_file_prefix>
input_file_is, 				// path/file.c => <input_file_prefix>.is
input_file_working_copy,	// path/file.c => <input_file_prefix>.c
input_file_no_extention;	// path/file.c => path/file

#if defined(_EXPERIMENT_MODE) || defined(_QUERY_LOG)
void copy_file(const char *source, const char *destination) {
    std::ifstream  src(source, std::ios::binary);
    std::ofstream  dst(destination, std::ios::binary);
    dst << src.rdbuf();
}
#endif
#ifdef _QUERY_LOG
std::ofstream QUERY_LOG("queries.log");

bool report_query(const list<int> &word, bool result, const char type, const char *respondent) {
	cout << "in report_query" << endl;
  QUERY_LOG << type << ';';
  std::copy(word.begin(), word.end(), std::ostream_iterator<int>(QUERY_LOG, " "));
  QUERY_LOG << ';' << std::boolalpha << result << ';' << respondent << std::endl;
  return result;
}

bool report_membership(const list<int> &word, bool result, const char *respondent) {
  return report_query(word, result, 'M', respondent);
}

bool report_conjecture(const std::list<int> &word, int result) {
  return report_query(word, result, 'C', "run_backend");
}
#else
bool report_membership(const list<int> &word, bool result, const char *respondent) { return result; }

bool report_conjecture(const std::list<int> &word, int result) { return result; }
#endif

unsigned word_length, unwind = 0;
// ~MDC 'User bound'
ostringstream unwind_s;
ostringstream unwind_setlimit;

// CBMC membership query cache
#ifdef _EXPERIMENT_MODE
enum membership_query_cache_resultt {
    IN_LANGUAGE,
    NOT_IN_LANGUAGE,
    NO_ENTRY_FOUND
};
#ifndef _DISABLE_CACHE
typedef boost::unordered_map<std::list<int>, bool> membership_query_cachet;
membership_query_cachet MEMBERSHIP_QUERY_CACHE;

membership_query_cache_resultt lookup_query(const std::list<int> &query) {
    const membership_query_cachet::const_iterator it(MEMBERSHIP_QUERY_CACHE.find(query));
    if(MEMBERSHIP_QUERY_CACHE.end() == it) { return NO_ENTRY_FOUND; }
    return it->second ? IN_LANGUAGE : NOT_IN_LANGUAGE;
}

void remember_query(const std::list<int> &query, bool result) { MEMBERSHIP_QUERY_CACHE.insert(std::make_pair(query, result)); }
#else
membership_query_cache_resultt lookup_query(const std::list<int> &query) { return NO_ENTRY_FOUND; }
void remember_query(const std::list<int> &query, bool result) { }
#endif
#endif

// Backend modes
static enum {
  CBMC, SYMEX, SYMEX_CBMC, LOG_CBMC, LOG
} backend = CBMC;

//~MDC Needs to be addressed
void rewrite_branch( string name, int num)
{
    
}

// We copy the contents file.f to file.is ("interesting set") in the format which is expected by goto-instrument for the call-sequence-check.
void create_interesting_set(FILE *f) {
    char name[100];
    string st = "rm " + input_file_is;
    run(st.c_str()); // remove old .is file, even if we do not create a new one.
    FILE *func_names_for_goto_inst = fopen(input_file_is.c_str(), "w");
    while (!feof(f)) {
        if (fscanf(f, "%s", name) != 1) continue;
        fprintf(func_names_for_goto_inst, "%s\n", name);
    }
    fclose(func_names_for_goto_inst);
}

void add_learn_instrumentation(string input_file, string link) {
    
    stringstream tmp;
    
    // ~MDC Convert .c source into 'master' object file
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-cl " << link << " " << input_file << " /Fo" << input_file_exe << "\"";
#else
    "goto-cc " << link << " " << input_file << " -o " << input_file_exe;
#endif
    
    run(tmp.str().c_str());
    
    stringstream st, st1;
    st << input_file_no_extention << ".f";
    FILE *user_func_names = fopen(st.str().c_str() , "r");
    
    if (user_func_names == NULL) {
        
        cout << "Using all function names (other than 'main'). A restricted list can be given in a file " << input_file_no_extention << ".f" << endl;
        
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
        cout << "found .f file " << endl;
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
    
}

int generate_func_names(int letter) {
    
    add_learn_instrumentation(input_file_working_copy, "-c");
    
    // ~MDC Manually add main for consistency with original version, may not be necessary.
    FILE *func_names_add_main = fopen(FUNC_NAMES, "a");
    fprintf(func_names_add_main, "%s\n", "main");
    fclose(func_names_add_main);
    
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
    input_file_name_base,
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
    input_file_is			  = input_file_prefix + ".is"; // goto-instrument tacitly expects .is file to be present. Do not change.
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
        else if (!strcmp(argv[i], "--symex")) { backend = SYMEX; }
        else if (!strcmp(argv[i], "--mixed")) { backend = SYMEX_CBMC; }
		else if (!strcmp(argv[i], "--rs"))    { learning_alg = Learn_RS;} // still buggy -- do not use. apparently the reason is that the positive feedback traces from the conjecture are inserted into positive_queries_filter, despite the fact that these are suffixes and not full traces.
        else Abort(string("wrong argument: ") + string(argv[i]));
    }
    
    if (alphabet_size == 0 && !instrument_branches && !instrument_functions) Abort("alphabet size must be > 0, or --auto should be used.");
}

void remove_labels() {
    ostringstream tmp;
    tmp << "rm -f " << AUTO_LABELS;
    run(tmp.str().c_str());
}

void remove_positive_queries() {
    ostringstream tmp;
    tmp << "rm -f " << POSITIVE_QUERIES_FILE << "; echo > " << POSITIVE_QUERIES_FILE;	// we need a positives_query file because it is included from other files.
    run(tmp.str().c_str());
}

void remove_files() {
    remove_labels();
#ifndef _EXPERIMENT_MODE
    remove_positive_queries();
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

void visualise_automaton(finite_automaton* a, bool show_immediately, string output_name) { //~MDC
	
    streambuf* strm_buffer = cout.rdbuf();
	output_name.append(".dot");
    ofstream dot(output_name.c_str());
    cout.rdbuf (dot.rdbuf());
    cout << a->visualize_existing();
    dot.close();
    
    cout.rdbuf (strm_buffer);
    
	stringstream display_command;
	display_command << "dotty " << output_name;
	
    if ( show_immediately ) run(display_command.str().c_str());
	
}

void visualise_automaton(finite_automaton* a, bool show_immediately) { // ~MDC
	
	visualise_automaton(a, show_immediately, "a");
}

// With sinks, dominators and doomed.
void visualise_automaton_full(finite_automaton* a, bool show_immediately, string output_name) { //~MDC
	
    streambuf* strm_buffer = cout.rdbuf();	
    ofstream candidate(CONJECTURE_DATA);    
    cout.rdbuf (candidate.rdbuf());
    cout << a->write(); 
    candidate.close();
    cout.rdbuf (strm_buffer); 
	
	post_process();
	
	a->store_file_data();
	
    visualise_automaton(a, show_immediately, output_name);
	
}
	
void visualise_automaton_full(finite_automaton* a, bool show_immediately) { //~MDC
	
   visualise_automaton_full(a, show_immediately, "a");
	
}

/*******************************  Learn  ****************************/
list<int> get_CounterExample(int alphabetsize) {
    
    list<int> ce;
    int  i;
    int length;
	int feedback[2];
    ifstream read(MODEL);
    read >> *feedback;
	
	// We use the result only if it is positive feedback. If it is negative feedback we need to recheck it.
    // The difference between positive and negative feedback is emenating from how we catch negative feedbacks. We do so by the 'trap', which extends any path reaching the end with an arbitrary sequence.
    // if that sequence happens to drive us to an accepting state in the current conjecture, we conclude that this is a negative feedback. But there can be a different input that creates exactly the same path
    // and indeed violates the assertion. So we query the counterexample, to see if it happens to be positive.
    if (*feedback) conjecture_result = CONJ_TRUE; 

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

int run_with_numeric_result(const char* cmd) {
    if (verbose) {cout << endl << "---------- external command -----------" << endl << cmd << endl;}
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return -1;
    char buffer[256];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 256, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    if (verbose) {cout << endl << "---------------------------------------" << endl;}
    cout.flush();
    
    std::stringstream ss(result);
    std::string item;
    while (std::getline(ss, item, '\n')) {
        boost::trim(item);
        if (isdigit(item.c_str()[0])) {
            return atoi(item.c_str());
        }
    }
    
    return -1;
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

int run_symex(bool membership) {
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

    /*// Remove multi-dimensional arrays.
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-instrument --remove-multidim-array " << "learn" << input_file_exe << " " << "learn" << input_file_exe << "\"";
#else
	"goto-instrument --remove-multidim-array " << "learn" << input_file_exe << " " << "learn" << input_file_exe;
#endif

    run(tmp.str().c_str());*/

    // ~MDC Run combined objects through CBMC
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"" <<
#endif
    "symex -Iansi-c-lib --show-trace --unwind " << unwind_s.str() << " --unwindset Learn_trap.0:" << unwind_setlimit.str() << ",check_conjecture.0:" << unwind_setlimit.str() << ",check_conjecture_at_trap.0:" << unwind_setlimit.str() << " --no-unwinding-assertions --xml-ui " << "learn" << input_file_exe << " > " <<
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
        string("cmd /c ") + string("\"") + CE_SYMEX + string(" ") + tmp_file + "\"";
#else
        CE_SYMEX + string(" ") + tmp_file;
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

namespace {
const char QUERY_FILE[] = "query-database.log";

void get_letters(list<int> &result, const std::string &line) {
  result.clear();
  vector<string> letters;
  boost::split(letters, line, boost::is_any_of(" "));
  for(vector<string>::const_iterator it(letters.begin()); it != letters.end(); ++it) {
    const std::string &letter(*it);
    if(!letter.empty())
      result.push_back(boost::lexical_cast<int>(letter));
  }
}

int write_counterexample(const list<int> &letters, char feedback) {
  // Manually write counterexample file
  ofstream model(MODEL);
  model << "    " << feedback << endl; // Word missing
  model << "    " << letters.size() << endl;
  model << "     ";
  copy(letters.begin(), letters.end(), ostream_iterator<int>(model, " "));
  return 0;
}

bool is_query_not_in_log(const list<int> &word) {
  ostringstream oss;
  copy(word.begin(), word.end(), ostream_iterator<int>(oss, " "));
  const string word_line(oss.str());

  string line;
  for (ifstream log_file(QUERY_FILE); getline(log_file, line); )
    if (word_line == line)
      return false;

  return true;
}

bool log_conjecture_enumerate(list<int> &word, const finite_automaton &a, int state) {
  if (word.size() >= word_length)
    return false;

  const map<int, set<int> > &delta=a.transitions.find(state)->second;
  for(map<int, set<int> >::const_iterator it(delta.begin()); it != delta.end(); ++it) {
    assert(it->second.size() == 1); // DFA
    const int letter(it->first);
    const int next_state(*it->second.begin());
    word.push_back(letter);
    if (a.output_mapping.find(next_state)->second) {
      if (is_query_not_in_log(word))
        return true;
    } else if (log_conjecture_enumerate(word, a, next_state))
      return true;
    word.pop_back();
  }
  return false;
}

void add_last_ce_to_logfile() {
  const list<int> ce=get_CounterExample(alphabet_size);
  ofstream ofs(QUERY_FILE, ofstream::app);
  for(list<int>::const_iterator it=ce.begin(); it != ce.end(); ++it) {
    ofs << *it << ' ';
  }
  ofs << endl;
}

bool log_conjecture_pre_check_positive_feedback(const conjecture &cj, list<int> &path) {
	cout << "in log_conjecture_pre_check_positive_feedback" << endl;
  const finite_automaton &a(static_cast<const finite_automaton &>(cj));
  const int initial_state=*a.initial_states.begin();

  // Check log file for queries not in automaton (positive feedback)
  string line;
  for (ifstream log_file(QUERY_FILE); getline(log_file, line); ) {
    get_letters(path, line);
    if (path.size() > word_length) continue;

    int state = initial_state;
    for(list<int>::iterator it(path.begin()); it != path.end(); ++it)
      state = *a.transitions.find(state)->second.find(*it)->second.begin();

    if(!a.output_mapping.find(state)->second)
    {
		  cout << "found positive feedback " << endl;	
		  conjecture_result = CONJ_TRUE;
      return false;
    }
  }
  path.clear();
  return true; 
}
}

int run_log_conjecture(bool include_negative_feedback = false) {
  assert(CURRENT_CONJECTURE);
  const finite_automaton &a(*CURRENT_CONJECTURE);
  CURRENT_CONJECTURE = 0;
  
  // Check log file for queries not in automaton (positive feedback)
  list<int> letters;
  if (!log_conjecture_pre_check_positive_feedback(a, letters))
    return write_counterexample(letters, '1');
  
  // Check automaton for accepted words not in query file (negative feedback)
  // XXX: Doesn't scale
  if (include_negative_feedback)
  {
    letters.clear();
    const int initial_state=*a.initial_states.begin();
    if (log_conjecture_enumerate(letters, a, initial_state))
      return write_counterexample(letters, '0');
  }

  return 1; // Equivalent
}

int run_log(bool membership) {
  if (!membership)
    return run_log_conjecture();
  assert(CURRENT_QUERY);
  const list<int> &query(*CURRENT_QUERY);
  CURRENT_QUERY = 0;
  ostringstream convert;
  copy(query.begin(), query.end(), ostream_iterator<int>(convert, " "));
  const string query_line(convert.str());
  ifstream log_file(QUERY_FILE);
  string line;
  while (getline(log_file, line))
    if (query_line == line)
      return 0; // In language

  return 1; // Not in language
}

int run_mixed(bool membership) {
	return membership ? run_symex(true) : run_cbmc(false);
}

int run_backend(bool membership) {
	switch (backend) {
	case CBMC:
		return run_cbmc(membership);
	case SYMEX:
		return run_symex(membership);
	case LOG:
	  return run_log(membership);
	case SYMEX_CBMC:
		return run_mixed(membership);
	case LOG_CBMC:
		return membership ? run_log(membership) : run_cbmc(membership);
	}
	return -1;
} 

// searches for a lasso-shaped path starting at an initial state and the loop goes through an accepting state. If found, this is a negative feedback
// and we answer false to the conjecture. If the answer is true (no path was found), then we cannot conclude anything. 
bool answer_Conjecture_pre_check(conjecture * cj, std::list<int>& path) {
	
	cout << "in conjecture_pre_check" << endl;
	finite_automaton * a = dynamic_cast<finite_automaton*> (cj);	
	bool res = a-> find_lasso(path);
	std::list<int>::iterator it;
	
	if (res) {
		cout << "found negative feedback " << endl;	
		conjecture_result = CONJ_FALSE;
	} else {
		path.clear();
	}
	return !res; // false if path found, to be compatible with answer_Conjecture_cbmc. 
}

bool answer_Conjecture_cbmc(conjecture * cj) {    
    assert(cj != NULL);    
    cbmc_conjectures++;
    cout << endl << "Conjecture:" << endl << endl;
	finite_automaton * a = dynamic_cast<finite_automaton*> (cj);	
    cout << a->visualize();
    streambuf* strm_buffer = cout.rdbuf();		// redirecting cout to a.out. We need this because visualize() returns an ostream.
    // ~MDC Temporary disable of visualising intermediate cbmc_conjectures
    //ofstream dot("a.dot");
    //cout.rdbuf (dot.rdbuf());
    //cout << a->visualize();
    //dot.close();
    
    ofstream candidate(CONJECTURE_DATA);    // same thing for write()
    cout.rdbuf (candidate.rdbuf());
    cout << a->write(); // write() is a rewrite of the original lib function.
    candidate.close();
    cout.rdbuf (strm_buffer); // reverting cout to its normal behavior.
    string st;
	//cout << "press enter to continue" << endl;
	//cin >>  st;
  CURRENT_CONJECTURE = a;
	int res = run_backend(false);
    cout << " " << (res != 0 ? "(yes - equivalent)" : "(no - not equivalent)") << endl;
    return (res != 0);
}

void positive_queries(list<int> query) {
	  list<int>::iterator it;
    unsigned size = query.size();
    ostringstream ist;
  	cout<< "positive query= ";
	  ist << "echo \"if (_Learn_idx == " << size << " && ";
    int i = 0;
    for (it = query.begin(); it != query.end(); ++i)
    {
		cout << *it << " ";
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
    
    // The query is right after conjecture, and we trust the result. 
	if (conjecture_result != CONJ_UNKNOWN) {
		if (conjecture_result == CONJ_FALSE) {
			cout << "Feedback from conjecture (no)!" << endl;
			conjecture_result = CONJ_UNKNOWN;		
			return 0;
		}
		if (conjecture_result == CONJ_TRUE) {	
			cout << "Feedback from conjecture (yes)!" << endl;
			conjecture_result = CONJ_UNKNOWN;		
			positive_queries(query);        
			return 1;
		}
	}
	if (query.size() > word_length)
    {
        cout << "Word too long!" << endl;
        return 0;
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

#ifdef _LOG_PRE_CHECK
    // Entries in the query log (e.g. generated by smid) are definitely in the language.
    CURRENT_QUERY=&query;
    if (!run_log(true)) return 1;
#endif 

    return 2;
}

//only one of those should be defined
// #define org   // org = original membership_cfg_checks below, which only saves the last prefix, in contrast to the new one that saves them all. 
//#define cfg_checks_list  // with bad_prefixes= list<list<int>>
#define cfg_checks_hash
//#define org

#ifdef cfg_checks_hash

unordered_set<string> bad_prefixes;

string hashlist(list<int>& mylist, int bound) {
	stringstream st;
	int i = 0;
	if (alphabet_size < 10) 
		for (list<int>::iterator it = mylist.begin(); i< bound && it != mylist.end();++it, ++i) {
			st << *it;
		}
	else
		for (list<int>::iterator it = mylist.begin(); i< bound && it != mylist.end();++it, ++i) {
			st << *it << ",";
		}
	return st.str();
}

bool membership_cfg_checks(list<int>& query) {
	cout << "in mem_cfg_checks. Size of bad_prefixes = " << bad_prefixes.size() << " query size = " << query.size() << endl;
	list<int>::iterator it;
    stringstream st;
    bool same_prefix; 
	int length = query.size();
	for (int i = 1; i<= length; ++i)
		if (bad_prefixes.find(hashlist(query, i)) != bad_prefixes.end()) {
			cout << "cfg (prefix)" << endl;
			++cfg_prefix;
			return false;
		}
	
	for (it = query.begin(); it != query.end(); ++it) // go over query
		st << func_name[*it] << endl;
	

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
    if (res == 1) {
        cout << "cfg! ";
        // now we find where the point of failure was
        tmp.str("");
        tmp << "tail -n 1 tmp1 > _seq_failure.res";
        run(tmp.str().c_str());
        seq_res = fopen ("_seq_failure.res", "r");
		int failure_point;
        if (fscanf(seq_res, "%d", &failure_point) != 1) Abort("cannot read _seq_failure.res");
        fclose(seq_res);		
        bad_prefixes.insert(hashlist(query, failure_point));
        return false;
    }
    return true;
}
#endif

#ifdef cfg_checks_list
list<list<int> > bad_prefixes;

bool membership_cfg_checks(list<int> query) {
    
    
	cout << "in mem_cfg_checks. Size of bad_prefixes = " << bad_prefixes.size() << " query size = " << query.size() << endl;
	list<int>::iterator it;
    stringstream st;
    bool same_prefix; 
	for (list<list<int> >::iterator bad_prefixes_it = bad_prefixes.begin(); bad_prefixes_it != bad_prefixes.end(); ++bad_prefixes_it) { // for each bad prefix
		same_prefix = true;
		list<int>::iterator bad_prefix_it = (*bad_prefixes_it).begin();
		for (it = query.begin(); same_prefix && it != query.end(); ++it) // go over query
			if (*it >= min_func_idx) {
				if (bad_prefix_it == (*bad_prefixes_it).end()) {  // same prefix as the previous failed one; we skip cfg check and return false.
					cout << "cfg (prefix)" << endl;
					++cfg_prefix;
					return false;
				}
				if (*bad_prefix_it != *it) same_prefix = false; // will abort this prefix
				++bad_prefix_it;
			}
	}
	
	for (it = query.begin(); it != query.end(); ++it) // go over query
		st << func_name[*it] << endl;
	

	cout << "st  = " << st.str() << endl;
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
		int failure_point;
        if (fscanf(seq_res, "%d", &failure_point) != 1) Abort("cannot read _seq_failure.res");
        fclose(seq_res);
		list<int> bad_prefix;
		
        list<int>::iterator tmp_it = query.begin();
        cout << "bad prefix = ";
        for (int i = 0; i < failure_point; ++i)
        {
            bad_prefix.push_back(*tmp_it);
            cout << *tmp_it << " ";
            ++tmp_it;
        }
		bad_prefixes.push_back(bad_prefix);
        cout << endl;
        return false;
    }
    return true;
}
#endif

#ifdef org
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
#endif

bool answer_Membership(list<int> query) {
    
    list<int>::iterator it;
    stringstream st;
    
    mem_queries++;
    cout << "Please classify the word: ";
    for (it = query.begin(); it != query.end(); ++it ) cout << ' ' << *it;
    cout << " ";
    
    // cheap pre-checks
    char pre_res = membership_pre_checks(query);  // 0 - false, 1 - true, 2 - no finding
    if (pre_res != 2) return report_membership(query, (bool) pre_res, "membership_pre_checks");
    
#ifdef _EXPERIMENT_MODE
    const membership_query_cache_resultt cached_result(lookup_query(query));
    if(NO_ENTRY_FOUND != cached_result) {
        cout << "Cached membership query!" << endl;
        ++cache_mem_queries;
        return report_membership(query, IN_LANGUAGE == cached_result, "membership_pre_checks_cache");
    }
#endif
    
    // if instrumenting function calls, word has to be compatible with the cfg
    if (instrument_functions && !membership_cfg_checks(query)) {
#ifdef _EXPERIMENT_MODE
        remember_query(query, false);
#endif
        return report_membership(query, false, "membership_cfg_checks");
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
                if (saw_assert_test_letter) {cout << *it << " ! \n"; return report_membership(query, false, "saw_assert_test_letter");;}
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
    
    CURRENT_QUERY = &query;
    const int res = run_backend(true);
    const bool cbmc_result = (res == 0);
#ifdef _EXPERIMENT_MODE
    if(cbmc_result) { remember_query(query, cbmc_result); }
#endif
    
    cout << " " << (cbmc_result ? "(yes)" : "(no)") << endl;
    // updating the positive_queries_file: this will block paths that correspond to membership that we already answered positively.
    if (cbmc_result) positive_queries(query);

    return report_membership(query, cbmc_result, "run_backend");
}

// need template because we invoke this function with two types of learning algorithm, which change the way we call algorithm() below. 
template <typename T> 
finite_automaton* learn() {
	
    // Create new knowledge-base. In this case, we choose bool as type for the knowledge-base.
    knowledgebase<bool> base;
    conjecture *result = NULL;
    
    // Create learning algorithm (Angluin/rivest-schapiro L*) without a logger (2nd argument is NULL) and alphabet size alphabet_size
	T  algorithm(&base, NULL, alphabet_size);
	
    bool conjectured = false;
    //int counter = 0;
    do {
        // Advance the learning algorithm
        conjecture *cj = algorithm.advance();		
        // Resolve membership queries
        if (cj == NULL) {
            //counter++;
            // retrieve queries
			cout << "** membership " << endl;
			list<list<int> > queries = base.get_queries();
            
            // iterate through all queries
            list<list<int> >::iterator li;
            for (li = queries.begin(); li != queries.end(); li++) {
                
                // Answer query				
                bool a = answer_Membership(*li);
				if (learning_alg == Learn_RS && prev_conjecture_result == CONJ_UNKNOWN) { 
					prev_conjecture_result = a ? CONJ_TRUE : CONJ_FALSE; 
					cout << "query = " ;  // why is not saying 'feedback from query?'
					for (list<int>::iterator it = li->begin(); it != li -> end(); ++it) cout << *it << " " ; 
					cout << "now prev_conjecture_result = " << prev_conjecture_result << endl;
				}
                // Add answer to knowledge-base
                base.add_knowledge(*li, a);
            }
            
            //	if (counter > 1 && conjectured) exit(1);
            //		if (conjectured) exit(1);
            conjectured = false;
        }
        // Resolve equivalence queries
        else {
            //counter++;
			//if (conjectures == 1) exit(1);
			cout << "** conjecture " << endl;
			conjectures++;
			cout << "conjectures = " << conjectures << endl;
            if (conjectured) 
            {
              cerr << "last counterexample corresponds to a nondeterministic path: it can either belong or not belong to the language. " << endl;
              return 0;
            }
            conjectured = true;
			std::list<int> ce; 
			static std::list<int> prev_ce;
			bool is_equivalent = true;

			if (learning_alg == Learn_RS && prev_ce.size() > 0) {
				finite_automaton *a = dynamic_cast<finite_automaton*> (cj);	
				bool in_language = a->contains(prev_ce);
				cout << "prev_ce.size = " << prev_ce.size() << "prev_conjecture_result = " << prev_conjecture_result << " in_language = " << in_language << endl;
				if ((prev_conjecture_result == CONJ_TRUE && !in_language) || (prev_conjecture_result == CONJ_FALSE && in_language)) {
					ce = prev_ce;
					conjecture_result = prev_conjecture_result;
					cout << "recycling counterexample"  << endl;
					is_equivalent = false;
				}
			}

#ifdef _LOG_PRE_CHECK
      if (is_equivalent)
        is_equivalent = log_conjecture_pre_check_positive_feedback(*cj, ce);
#endif

			if (is_equivalent)
				is_equivalent = answer_Conjecture_pre_check(cj, ce); // graph analysis, searches for back edges, and fills ce if found one. 			

			if (is_equivalent) 
				is_equivalent = answer_Conjecture_cbmc(cj); //  cbmc call			
            
            if (is_equivalent) {
            	report_conjecture(std::list<int>(), -1);
                result = cj;
            } else {
                // Get a counterexample
                if (ce.size() == 0) 
					ce = get_CounterExample(alphabet_size); // this means that we called cbmc rather than found a counterexample with the precheck.
				
                report_conjecture(ce, conjecture_result);				
				
				if (learning_alg == Learn_RS)  {
					prev_conjecture_result = CONJ_UNKNOWN;
					prev_ce = ce;
				}
                //++counter;
                //if (counter == 1) exit(1);
                
                // Add counter-example to algorithm
                algorithm.add_counterexample(ce);
                //exit(1);
                // Delete old conjecture
                delete cj;
            }
        }
        
        
    } while (result == NULL);
    
	finite_automaton* result_as_automaton = dynamic_cast<finite_automaton*> (result);
	
	#ifdef _EXPERIMENT_MODE
	
    	visualise_automaton_full(result_as_automaton, false);	// we do it inside learn because result is a pointer to a local object.
    
	#else 
	
		visualise_automaton_full(result_as_automaton, true);
	
	#endif
		
    return result_as_automaton;
	
}

void exit_learn() {
    
	remove_files();
	
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
	MEMBERSHIP_QUERY_CACHE.clear();
	func_name.clear();
    alphabet_size = 0;
}

int count_nodes(finite_automaton* conjectured_automaton) {
	
    return conjectured_automaton->state_count - 1;
    
}

int count_edges(finite_automaton* conjectured_automaton) {
    
    return conjectured_automaton->count_transitions();
    
}

bool has_loops() {
    stringstream tmp;
    tmp.str("");
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-instrument " << input_file_exe << " --show-loops " << input_file_exe << " | wc -l\"";
#else
    "goto-instrument " << input_file_exe << " --show-loops " << input_file_exe << " | wc -l";
#endif
    
    if (run_with_numeric_result(tmp.str().c_str()) > 1)
        return true;
    
    return false;
}

int estimate_wordlength() {
    
    add_learn_instrumentation(input_file_name_full, "");
    
    //
    
    stringstream tmp;
    tmp <<
#ifdef _MYWIN32
    "cmd /c \"goto-instrument --learn-word-length " << input_file_exe << " " << input_file_exe << "\"";
#else
    "goto-instrument --learn-word-length " << input_file_exe << " " << input_file_exe;
#endif
    
    return run_with_numeric_result(tmp.str().c_str());
    
}

bool test_convergence(finite_automaton** conjectured_automata, int lowest_word_length, int word_length, int user_bound) {
    // ~MDC: Sets of automata that must match to signal convergence (i.e. 1 = 1 set = 2 automata)
    int NUMBER_MATCHING = 1;
    bool matching = false;
    if ( (word_length - lowest_word_length) >= NUMBER_MATCHING ) {
		
        matching = true;
        
        for ( int current_length = word_length - NUMBER_MATCHING; current_length < word_length; current_length++ ) {
            
			//if ( conjectured_automata[current_length]->recursive_non_accepting() || conjectured_automata[current_length + 1]->recursive_non_accepting() ) matching = false;
			
            if (conjectured_automata[current_length]->get_final_states().size() == 0 || conjectured_automata[current_length + 1]->get_final_states().size() == 0 ) matching = false;
           
            if (count_nodes(conjectured_automata[current_length]) != count_nodes(conjectured_automata[current_length + 1]) || count_edges(conjectured_automata[current_length]) != count_edges(conjectured_automata[current_length + 1])) {
                matching = false;
                break;
            }
			
        }
    }
	
    return matching;
}

#endif

finite_automaton* reduce_to_accepting_paths(finite_automaton* &A, string name) { // ~MDC
	
	std::list<std::list<int> > paths_list = A->find_all_paths();
	finite_automaton* reduced_automaton = new finite_automaton;
	
	list<int> automaton_states;
	for (std::list<std::list<int> >::const_iterator paths=paths_list.begin(); paths!=paths_list.end(); ++paths) {
		
		int last_state = -1;
		for (std::list<int>::const_iterator path=paths->begin(); path!=paths->end(); ++path) {
			if (last_state > -1 ) { 
				std::vector<int> transitions = A->get_transitions(last_state, *path);
				for (std::vector<int>::const_iterator transition=transitions.begin(); transition!=transitions.end(); ++transition) {
					reduced_automaton->transitions[last_state][*transition].insert(*path);
					reduced_automaton->label[*transition] = A->transition_to_label(*transition);
				}
			} else {
				if(reduced_automaton->initial_states.find(*path) == reduced_automaton->initial_states.end()) { 
					reduced_automaton->initial_states.insert(*path);
				}
			}
			reduced_automaton->output_mapping[*path] = false;
			automaton_states.push_back(*path);
			last_state = *path;
		}
		reduced_automaton->output_mapping[last_state] = true;
		last_state = -1;
	}
	
	automaton_states.unique();
	reduced_automaton->state_count = automaton_states.size();
	
	reduced_automaton->is_deterministic = true;
	reduced_automaton->valid = true;
	
	visualise_automaton(reduced_automaton, true, name);
	
	return reduced_automaton;
	
}

finite_automaton* reduce_to_accepting_paths(finite_automaton* &A) { // ~MDC
	
	return reduce_to_accepting_paths(A, "a");
		
}

finite_automaton* intersect(finite_automaton* &A, finite_automaton* &B) { // ~MDC
	
	if ( A->input_alphabet_size != B->input_alphabet_size) cout << "Automata alphabets should match." << endl;
	
	std::map<std::pair<int, int>, int> states_to_numbers;
	
	finite_automaton* intersection_automaton = new finite_automaton;

	int state_count = 0;
	
	int MAX_ALPHABET = A->input_alphabet_size;
	
	// SA∩B=SA×SB
	for ( int Sa = 0; Sa < A->state_count; Sa++ ) {
		
		for ( int Sb = 0; Sb < B->state_count; Sb++ ) {
			
			std::pair<int, int> Sab( Sa, Sb );
			
			std::pair<std::pair<int, int>, int> Sab_and_count(Sab, state_count);
			states_to_numbers.insert( Sab_and_count );
			
			intersection_automaton->output_mapping[state_count] = false;
			
			state_count++;
		
		}
		
	}
	
	// Set number of states
	intersection_automaton->state_count = state_count;
	
	// iA∩B=⟨iA,iB⟩
	for (std::set<int>::const_iterator iA = A->initial_states.begin(); iA != A->initial_states.end(); ++iA) {
		for (std::set<int>::const_iterator iB = B->initial_states.begin(); iB != B->initial_states.end(); ++iB) {
			intersection_automaton->initial_states.insert(states_to_numbers[std::pair<int, int>(*iA, *iB)]);
		}
	}
	
	// FA∩B=FA×FB;
	for (std::map<int, bool>::const_iterator fA = A->output_mapping.begin(); fA != A->output_mapping.end(); ++fA) {
		for (std::map<int, bool>::const_iterator fB = B->output_mapping.begin(); fB != B->output_mapping.end(); ++fB) {
			if ( fA->second && fB->second ) {
				intersection_automaton->output_mapping[states_to_numbers[std::pair<int, int>(fA->first, fB->first)]] = true;
			}
		}
	}
	
	// for any letter α ∈ Σ
	for (int l = 0; l < MAX_ALPHABET; l++) {

		// Find the states in A connected by this letter
		std::vector<std::pair<int, int> > A_connections = A->nodes_connecting_letter(A->index_of_label(A->transition_to_label(l)));
	
		// Find the states in B connected by this letter
		std::vector<std::pair<int, int> > B_connections = B->nodes_connecting_letter(B->index_of_label(A->transition_to_label(l)));
	
		intersection_automaton->label[l] = A->transition_to_label(l);
		
		// Look through all states in A which are connected by this letter
		for (int i = 0; i < A_connections.size(); i++) {
			//p1,p2 ∈ SA
			// p1−→ A α −→ p2
			int p1 = A_connections[i].first;
			int p2 = A_connections[i].second;
			
			for (int j = 0; j < B_connections.size(); j++) {
				//q1,q2 ∈ SB
				// q1−→ A α −→ q2
				int q1 = B_connections[j].first;
				int q2 = B_connections[j].second;
				
				intersection_automaton->transitions[states_to_numbers[std::pair<int, int>(p1, q1)]][l].insert(states_to_numbers[std::pair<int, int>(p2, q2)]);
				
			}
				
		}
	
	}
	
	intersection_automaton->is_deterministic = true;
	intersection_automaton->valid = true;
	
	return intersection_automaton;
	
} 

#ifdef _EXPERIMENT_MODE
#define WORD_LENGTH_ARGUMENT_INDEX 2 
#define USER_BOUND_ARGUMENT_INDEX 7
#define LOG_EACH_BOUND false
#endif
/*******************************  main  ****************************/
int main(int argc, const char**argv) {

	std::vector<std::vector<const char*> > params;
	std::vector<finite_automaton*> program_versions;
	string version_a, version_b;
	
	if ( strcmp(argv[1], "--compare") == 0 ) {
		version_a = argv[2];
		version_b = argv[3];
		
		for ( int i = 2; i < 4; i++ ) {
			std::vector<const char*> argv_copy;
            argv_copy.push_back(argv[0]);
			for ( int j = i; j < argc; j++ ) {
				if (j == i) argv_copy.push_back(argv[j]);
				if (j > 3) argv_copy.push_back(argv[j]);
			}
			params.push_back(argv_copy);
		}
	} else {
		std::vector<const char*> argv_copy(argv, argv + argc);
		params.push_back(argv_copy);
	}
	
	for (std::vector<std::vector<const char*> >::const_iterator params_it = params.begin(), last_param = params.end(); params_it != last_param; ++params_it) {
	
        std::vector<const char*> argv_vector = *params_it;
        const char** argv_copy = &argv_vector[0];
	    parse_options(params_it->size(), argv_copy);
    
#ifdef _EXPERIMENT_MODE 
		
		int lower_bound = word_length;
		cout << "word length is " << lower_bound << endl;
		if ( lower_bound == 0 ) {
			
	    	lower_bound = estimate_wordlength();
    
	    	cout << "Estimating lower_bound as: " << lower_bound << endl;
    	
		}
		
#endif
    
	    struct timeval begin;
    
	    gettimeofday(&begin, NULL);
    
#ifdef _EXPERIMENT_MODE
    
	    //for(int user_bound = 1; user_bound < 4; ++user_bound) {
      for(int user_bound = 2; user_bound < 3; ++user_bound) { 
        
	    	int MAX_UPPER_BOUND = 13;

			finite_automaton *conjectured_automata[MAX_UPPER_BOUND + 1];
			std::fill(conjectured_automata, conjectured_automata + sizeof(conjectured_automata) / sizeof(conjectured_automata[0]), (finite_automaton *) 0);

	        remove_positive_queries();
        
	        for(int word_length = lower_bound; word_length <= MAX_UPPER_BOUND; ++word_length) {
            
	            std::ostringstream ss;
	            ss << user_bound;
	            const std::string user_bound_argument(ss.str());
	            argv_copy[USER_BOUND_ARGUMENT_INDEX] = user_bound_argument.c_str();
	            reset(ss);
	            ss << word_length;
	            const std::string word_length_argument(ss.str());
	            argv_copy[WORD_LENGTH_ARGUMENT_INDEX] = word_length_argument.c_str();
	            reset_global_variables();
            
	#endif
            
	            parse_options(params_it->size(), argv_copy);
	            remove_files();
	            preprocess_source();
	            init_auto_instrumentation();
	            init_word_length_file();
            
#ifdef _EXPERIMENT_MODE
            
              while(!(conjectured_automata[word_length] = (learning_alg == Learn_Angluin)? learn<angluin_simple_table<bool> >(): learn<rivest_schapire_table<bool> >()))
              {
                if (LOG_CBMC != backend)
                {
                  reset(ss);
                  ss << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length << ".log";
                  std::ofstream ofs(ss.str().c_str());
                  ofs << "last counterexample corresponds to a nondeterministic path: it can either belong or not belong to the language. " << endl;
                  break;
                }
                else
                  add_last_ce_to_logfile();
              }
              if (!conjectured_automata[word_length]) continue;
#else
              while(!(learning_alg == Learn_Angluin ? learn<angluin_simple_table<bool> >() : learn<rivest_schapire_table<bool> >()))
              {
                if (LOG_CBMC != backend)
                  exit(1);
                else
                  add_last_ce_to_logfile();
              }
#endif
            
#ifdef _EXPERIMENT_MODE
	            cout << "in experiment_mode" << endl;
	            reset(ss);
            
	            bool hasConverged = test_convergence(conjectured_automata, lower_bound, word_length, user_bound);
            	
	            if (hasConverged || LOG_EACH_BOUND) {
#endif
	                struct timeval end;
	                gettimeofday(&end, NULL);
	                double elapsed_secs = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000000.0;
                
#ifdef _EXPERIMENT_MODE
                
	                ss << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length << ".dot";
	                copy_file("a.dot", ss.str().c_str());
                
#ifdef _QUERY_LOG
                
	                reset(ss);
	                ss << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length << "-query.log";
	                copy_file("query.log", ss.str().c_str());
	                std::ofstream remove_log;
	                remove_log.open("queries.log", std::ofstream::out | std::ofstream::trunc);
	                remove_log.close();
#endif
                
#endif
                
	                cout << "membership queries: " << mem_queries << " (" << cbmc_mem_queries << " cbmc calls - " << (float)cbmc_mem_queries * 100/(float)mem_queries << "\%)" << " cfg queries: " << cfg_queries << " cfg queries (prefix): " << cfg_prefix << " membership cache queries: " << cache_mem_queries << " total conjectures: " << conjectures << " cbmc conjectures = " << cbmc_conjectures << endl;
	                cout << "Time: " << elapsed_secs << endl;
                
#ifdef _EXPERIMENT_MODE
                
	                std::stringstream final_automaton_path;
	                final_automaton_path << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length << ".dot";
                
	                std::stringstream final_automaton_stats_filename;
	                final_automaton_stats_filename << "learn_output/" << input_file_prefix << "-" << user_bound << "-" << word_length;
                
	                ofstream final_automaton_stats_file;
	                final_automaton_stats_file.open(final_automaton_stats_filename.str().c_str());
                
	                std::stringstream final_automaton_stats_info;
	                // Name, Lower Bound, Convergence Bound, Iterations (~MDC Needs updating), User Bound, Seconds gone (CPU), Nodes, Edges, mem queries, CBMC mem queries / total queries, Cache mem queries / total queries, Conjectures
	                final_automaton_stats_info << input_file_prefix << " & " << lower_bound << " & " << word_length << " & " << (word_length - lower_bound) << " & " << user_bound << " & " << elapsed_secs << " & " << count_nodes(conjectured_automata[word_length]) << " & " << count_edges(conjectured_automata[word_length]) << " & " << mem_queries << " & " << (float)cbmc_mem_queries * 100/(float)mem_queries << " & " << (float)cache_mem_queries * 100/(float)mem_queries << " & " << cbmc_conjectures;
                
	                final_automaton_stats_file << final_automaton_stats_info.str();
	                final_automaton_stats_file.close();
					
	                if ( hasConverged ) {
	                    cout << "Converged at: bwl = " << word_length << " b = " << user_bound << endl;
						visualise_automaton_full(conjectured_automata[word_length], true);
						program_versions.push_back(conjectured_automata[word_length]);
	                    // ~MDC Comment both to not break after first convergence
	                    MAX_UPPER_BOUND = word_length;
	                    break;
	                }
                
	            }
            
	        }
        
			if ( strcmp(argv[1], "--compare") != 0 ) {
		        for (int a = lower_bound; a <= MAX_UPPER_BOUND; a++) {
					if (conjectured_automata[a]) {
						delete conjectured_automata[a];
					}
				}
			}
        
	        if ( !has_loops() ) {
	            break;
	        }
        
	    }
		
		exit_learn();

#endif
	
	}
	  
	if ( strcmp(argv[1], "--compare") == 0 ) {
		
		program_versions[0]->clear_sinks();

		program_versions[1]->clear_sinks();
		
		program_versions[1]->invert_accepting();

		finite_automaton* a_inter_neg_b = intersect(program_versions[0], program_versions[1]);
		reduce_to_accepting_paths(a_inter_neg_b, version_a.append("_distinct"));
		
		program_versions[1]->invert_accepting();
		program_versions[0]->invert_accepting();
		
		finite_automaton* b_inter_neg_a = intersect(program_versions[1], program_versions[0]);
		reduce_to_accepting_paths(b_inter_neg_a, version_b.append("_distinct"));
		
	}
    
    return 0;
    
}

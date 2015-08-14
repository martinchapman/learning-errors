// file names: 

// included from conjecture_query.c: 
#define POSITIVE_QUERIES_FILE "positive_queries_filter.c"
// labels that will be used in conjecture.cpp:
#define LABELS "labels.data"
#define AUTO_LABELS "auto_labels.data"
#define AUTO_LABELS_FUNCTIONS "auto_labels_functions.data"
#define AUTO_LABELS_BRANCHES "auto_labels_branches.data"
// output of the get_func_names batch file:
#define FUNC_NAMES "func_names.data"
#define AUTOMATON "automaton.data"
#define DOMINATORS "dominators.data"
#define DOOMED "doomed.data"
#define SINKS "sinks.data"
#define DOMINATING_EDGES "dominating_edges.data"
#define CG "call_graph.data"
#define CFG_EDGES "cfg_edges.data"
#define CFG_CONNECTORS "cfg_connectors.data"
#define FUNC_PAIRS "func_pairs.data"


#define CONJECTURE_DATA "conjecture_data.c"
#define CONJECTURE_DATA_H "conjecture_data.h" // included from learn_code.c
#define MEMBERSHIP_DATA "membership_data.c"
#define MEMBERSHIP_DATA_H "membership_data.h"

#define WORD_LENGTH "word_length.c" 
#define MODE "mode.c"

#ifdef _MYWIN32
 // main batch file: 
 #define CE "ce.bat" 
 #define CE_SYMEX "./ce-symex.sh"
 #define GENERATE_CALL_GRAPH "generate_call_graph.bat"
 // retrieves function names from a goto-instrument output: 
 #define GET_FUNC_NAMES "get_func_names.bat"
 #define CONVERT "convert.bat"
 #define CFG2GRAPH "cfg2graph.bat"
#define CE_SYMEX "./ce-symex.sh"
#else
 #define CE "./ce.sh"
 #define CE_SYMEX "./ce-symex.sh"
 #define GENERATE_CALL_GRAPH "./generate_call_graph.sh"
 #define GET_FUNC_NAMES "./get_func_names.sh"
 #define CONVERT "./convert.sh"
 #define CFG2GRAPH "./cfg2graph.sh"
#endif

// ce of cbmc; generated in CE
#define MODEL "model.txt"

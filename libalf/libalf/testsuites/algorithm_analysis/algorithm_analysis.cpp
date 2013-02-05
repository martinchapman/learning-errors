/* $Id: algorithm_analysis.cpp 1344 2010-07-18 15:34:43Z davidpiegdon $
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
 * (c) 2008,2009 Lehrstuhl Softwaremodellierung und Verifikation (I2), RWTH Aachen University
 *           and Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 * Author: David R. Piegdon <david-i2@piegdon.de>
 *
 */

#include <time.h>

#include <iostream>
#include <ostream>
#include <iterator>
#include <fstream>
#include <algorithm>

#include <libalf/alf.h>
#include <libalf/algorithm_angluin.h>
#include <libalf/algorithm_NLstar.h>
#include <libalf/algorithm_kearns_vazirani.h>
#include <libalf/knowledgebase.h>

#include <liblangen/dfa_randomgenerator.h>
#include <liblangen/nfa_randomgenerator.h>
#include <liblangen/regex_randomgenerator.h>

#include <amore++/nondeterministic_finite_automaton.h>
#include <amore++/deterministic_finite_automaton.h>
#include <amore++/finite_automaton.h>

#include "amore_alf_glue.h"

using namespace std;
using namespace libalf;
using namespace liblangen;

int main(int argc, char**argv)
{
	int num_testcases, min_msize, max_msize, min_asize, max_asize, model_size_step;

	if(argc != 7) {
		cout << "please give the following parameters:\n"
			"\t1: number of testcase per construction method, alphabet size and model size\n"
			"\t2: minimal alphabet size\n"
			"\t3: maximal alphabet size\n"
			"\t4: minimal model size\n"
			"\t5: maximal model size\n"
			"\t6: model size steps\n";
		return 1;
	}

	num_testcases = atoi(argv[1]);
	min_asize = atoi(argv[2]);
	max_asize = atoi(argv[3]);
	min_msize = atoi(argv[4]);
	max_msize = atoi(argv[5]);
	model_size_step = atoi(argv[6]);

	dfa_randomgenerator dfa_rg;
	nfa_randomgenerator nfa_rg;
	regex_randomgenerator regex_rg;

	int method, model_size, alphabet_size, testcase_index;

	int model_index = 0;
	int max_model_index = num_testcases * (max_asize - min_asize + 1) * ((max_msize - min_msize)/model_size_step + 1) * 3 /* 3 different kinds of model generation */ - 1;

	ostream_logger log(&cout, LOGGER_DEBUG);
	knowledgebase<bool> base;
	char logline[1024];
	ofstream statfile;
	statfile.open("statistics");
	statfile << "# model_index alphabet_size method model_size mDFA_size RFSA_size - L*-membership L*-uniq_membership L*-equivalence L*-usecs-needed - L*col-membership L*col-uniq_membership L*col-equivalence L*col-usecs-needed - NL*-membership NL*-uniq_membership NL*-equivalence NL*-usecs-needed - KV-membership KV-uniq_membership KV-equivalence KV-usecs-needed\n";

	for(model_size = min_msize; model_size <= max_msize; model_size += model_size_step) {
		for(method = 0; method <= 2; method++) {
			for(alphabet_size = min_asize; alphabet_size <= max_asize; ++alphabet_size) {
				for(testcase_index = 0; testcase_index < num_testcases; ++testcase_index) {
					// construct automaton according to method
					amore::finite_automaton * model;

					bool f_is_dfa;
					int f_alphabet_size, f_state_count;
					std::set<int> f_initial, f_final;
					map<int, map<int, set<int> > > f_transitions;

model_too_big:
					// {{{ construct model
						if(method != 2) {
							if(method == 0) {
								// 0 == DFA
								if(!dfa_rg.generate(alphabet_size, model_size,
										f_is_dfa, f_alphabet_size, f_state_count, f_initial, f_final, f_transitions)) {
									cout << "failed to generate random DFA!\n";
									return 1;
								}
								dfa_rg.discard_tables(); // we need space
							} else {
								// 1 == NFA
								if(!nfa_rg.generate(alphabet_size, model_size, 2, 0.5, 0.5,
										f_is_dfa, f_alphabet_size, f_state_count, f_initial, f_final, f_transitions)) {
									cout << "failed to generate random NFA!\n";
									return 1;
								}
							}
							model = amore::construct_amore_automaton(f_is_dfa, f_alphabet_size, f_state_count, f_initial, f_final, f_transitions);
							if(!model) {
								cout << "failed to construct automaton from generated data!\n";
								return 1;
							}
						} else {
							// 2 == RegEx
							std::string regex;
							bool success;
							regex = regex_rg.generate(alphabet_size, model_size, 0.556, 0.278, 0.166);
							model = new amore::nondeterministic_finite_automaton(alphabet_size, regex.c_str(), success);
							if(!success) {
								cout << "failed to construct NFA from regex!\n";
								return 1;
							}
						}
					/// }}}

					int stat_size_model = model->get_state_count();

					// save model to file, then determinize and minimize model so we're faster {{{
						char modelfilename[128];
						ofstream modelfile;

						snprintf(modelfilename, 128, "model_%08d_%c.dot", model_index, (method == 2) ? 'R' : (method == 1) ? 'N' : (method == 0) ? 'D' : '?');

						modelfile.open(modelfilename);
						modelfile << model->visualize();
						modelfile.close();

						amore::finite_automaton * tmp;
						tmp = model;
						model = tmp->determinize();
						delete tmp;
						model->minimize();
					// }}}

					int stat_size_mDFA = model->get_state_count();

					if(stat_size_mDFA > max_msize * 2) {
						delete model;
						goto model_too_big;
					}

					log(LOGGER_INFO, "completed %5.1f%% [model %d/%d size %d] (current alphabet size %d, method %s, model size %d)   \r",
							(float)model_index / max_model_index * 100, model_index, max_model_index, stat_size_mDFA , alphabet_size,
							(method == 0) ? "rDFA" : (method == 1) ? "rNFA" : (method == 2) ? "rRegEx" : "[?]",
							model_size);

					// learn model with different algorithms
					learning_algorithm<bool> * alg;
					statistics stats[4];
					unsigned long long int usecs_needed[4];

					int stat_size_RFSA;

					for(int learner = 0; learner <= 3; learner++) {


						base.clear();
						switch (learner) {
							case 0: alg = new angluin_simple_table<bool>(&base, &log, alphabet_size); break;
							case 1: alg = new angluin_col_table<bool>(&base, &log, alphabet_size); break;
							case 2: alg = new NLstar_table<bool>(&base, &log, alphabet_size); break;
							case 3: alg = new kearns_vazirani<bool>(&base, &log, alphabet_size); break;
						}
						alg->enable_timing();

						bool equal = false;
						int iteration = 0;
						usecs_needed[learner] = 0;

						while(!equal) {
							conjecture * cj = NULL;

							while(cj == NULL) {
								cj = alg->advance();
								if(cj == NULL)
									stats[learner].queries.uniq_membership += amore_alf_glue::automaton_answer_knowledgebase(*model, base);
							}

							list<int> counterexample;
							stats[learner].queries.equivalence++;
							stats[learner].queries.membership = base.count_resolved_queries();
							log(LOGGER_DEBUG, "eq query. \r");
							// --
							if(amore_alf_glue::automaton_antichain_equivalence_query(*model, cj, counterexample)) {
							log(LOGGER_DEBUG, "completed \r");
								equal = true;
								if(learner == 2)
									stat_size_RFSA = dynamic_cast<libalf::finite_automaton*>(cj)->state_count;
							} else {
								alg->add_counterexample(counterexample);
							}
							delete cj;

							iteration++;
						}

						timing_statistics t = alg->get_timing_statistics();
						usecs_needed[learner] = t.user_sec * 1000000 + t.user_usec;

						delete alg;
					}

					// save stats:
					//		model_index alphabet_size method model_size mDFA_size RFSA_size
					// (L* stats)
					//		- membership uniq_membership equivalence usecs_needed
					// (L*_col stats)
					//		- membership uniq_membership equivalence usecs_needed
					// (NL* stats)
					//		- membership uniq_membership equivalence usecs_needed
					// (KV stats)
					//		- membership uniq_membership equivalence usecs_needed
					snprintf(logline, 1024, "%d %d %d %d %d %d - %d %d %d %llu - %d %d %d %llu - %d %d %d %llu - %d %d %d %llu\n",
							model_index, alphabet_size, method, stat_size_model, stat_size_mDFA, stat_size_RFSA,
							stats[0].queries.membership, stats[0].queries.uniq_membership, stats[0].queries.equivalence, usecs_needed[0],
							stats[1].queries.membership, stats[1].queries.uniq_membership, stats[1].queries.equivalence, usecs_needed[1],
							stats[2].queries.membership, stats[2].queries.uniq_membership, stats[2].queries.equivalence, usecs_needed[2],
							stats[3].queries.membership, stats[3].queries.uniq_membership, stats[3].queries.equivalence, usecs_needed[3]
							);

					statfile << logline;

					delete model;
					model_index++;
				}
			}
		}
	}

	log(LOGGER_INFO, "done. thanks for your (non)attention :-)\n");

	statfile.close();

	return 0;
}


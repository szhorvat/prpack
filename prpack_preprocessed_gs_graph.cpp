#include "prpack_preprocessed_gs_graph.h"
#include <algorithm>
using namespace prpack;
using namespace std;

prpack_preprocessed_gs_graph::prpack_preprocessed_gs_graph(prpack_adjacency_list* al) {
	num_vs = al->num_vs;
	num_es = al->num_es - al->num_self_es;
	heads = new int[num_es];
	tails = new int[num_vs];
	ii = new double[num_vs];
	inv_num_outlinks = new double[num_vs];
	fill(inv_num_outlinks, inv_num_outlinks + num_vs, 0);
	for (int tails_i = 0, heads_i = 0; tails_i < num_vs; ++tails_i) {
		tails[tails_i] = heads_i;
		ii[tails_i] = 0;
		int start_j = al->tails[tails_i];
		int end_j = (tails_i + 1 != num_vs) ? al->tails[tails_i + 1]: al->num_es;
		for (int j = start_j; j < end_j; ++j) {
			if (tails_i == al->heads[j])
				++ii[tails_i];
			else
				heads[heads_i++] = al->heads[j];
			++inv_num_outlinks[al->heads[j]];
		}
	}
	for (int i = 0; i < num_vs; ++i) {
		inv_num_outlinks[i] = (inv_num_outlinks[i] == 0) ? -1 : 1/inv_num_outlinks[i];
		ii[i] *= inv_num_outlinks[i];
	}
}


#include "graph_ud.h"

struct edge_t {
	size_t tv_index;
	weight_t weight;
} *close_edges;

static size_t find_min(const size_t N);

// construct Minimum Spanning Tree from vertex S using Prim algorithm
void MST_prim(const graph_ud& G, const size_t S)
{
	size_t i, j, k;

	close_edges = new edge_t[G.vnum];
	for (i = 0; i < G.vnum; ++i)
	{
		if (i == S)
			continue;
		close_edges[i].tv_index = S;
		close_edges[i].weight = G.adjmat[i * G.vnum + S];
	}
	close_edges[S].weight = WINU;
	for (i = 1; i < G.vnum; ++i)
	{
		k = find_min(G.vnum);
		std::cout << G.data[close_edges[k].tv_index] << '-' << G.data[k] << ',';
		close_edges[k].weight = WINU;	// add k in MST
		for (j = 0; j < G.vnum; ++j)
		{		// renew close_edges
			if (close_edges[j].weight != WINU && close_edges[j].weight > G.adjmat[k * G.vnum + j])
			{
				close_edges[j].tv_index = k;
				close_edges[j].weight = G.adjmat[k * G.vnum + j];
			}
		}
	}
	delete[] close_edges;
}

// find minimum index in close_edges
static size_t find_min(const size_t N)
{
	weight_t min;
	size_t i, r;

	r = 0;
	min = WINF;
	for (i = 0; i < N; ++i)
	{
		if (close_edges[i].weight == WINU)
			continue;
		if (close_edges[i].weight < min)
		{
			min = close_edges[i].weight;
			r = i;
		}
	}
	return r;
}
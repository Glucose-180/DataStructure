#include "graph_ud.h"

static void sort_edges(const graph_ud& G);

void MST_kruskal(const graph_ud& G)
{
	size_t* icc;
	size_t i, j, k;
	size_t cc1, cc2;

	icc = new size_t[G.vn];	// index of connected component
	for (i = 0; i < G.vn; ++i)
		icc[i] = i;
	sort_edges(G);
	for (i = j = 0; i < G.vn && j < G.en; ++j)
	{
		cc1 = icc[G.el[j].t1];	// two connected components of j-th edge
		cc2 = icc[G.el[j].t2];
		if (cc1 != cc2)
		{
			std::cout << G.vl[G.el[j].t1] << '-' << G.vl[G.el[j].t2] << ',';
			++i;
			for (k = 0; k < G.vn; ++k)	// merge two connected components
				if (icc[k] == cc2)
					icc[k] = cc1;
		}
	}
	delete[] icc;
}

// do bubblesort on edges of G
static void sort_edges(const graph_ud& G)
{
	size_t i, j;
	edge_t temp;

	for (j = G.en; j > 1; --j)
		for (i = 1; i < j; ++i)
		{
			if (G.el[i].weight < G.el[i - 1].weight)
			{
				temp = G.el[i];
				G.el[i] = G.el[i - 1];
				G.el[i - 1] = temp;
			}
		}
}
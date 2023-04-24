#include "graph_ud.h"

using namespace std;

int main()
{
	graph_ud g;
	size_t vn, en, i;

	cin >> vn >> en;
	g = create_graph(vn, en);
	for (i = 0; i < en; ++i)
	{
		cin >> g.el[i].t1 >> g.el[i].t2 >> g.el[i].weight;
	}
	MST_kruskal(g);
	return 0;
}

// create a graph with VN vertices and EN edges
graph_ud create_graph(const size_t VN, const size_t EN)
{
	graph_ud g;
	size_t i;

	g.vn = VN;
	g.en = EN;
	g.vl = new gnode_t[VN];
	g.el = new edge_t[EN];
	for (i = 0; i < VN; ++i)
		g.vl[i] = 'A' + i;
	return g;
}
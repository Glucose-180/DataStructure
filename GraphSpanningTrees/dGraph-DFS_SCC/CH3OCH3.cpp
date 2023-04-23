#include "graph_d.h"

using namespace std;

int main()
{
	graph_d g;
	size_t v;
	char c;
	size_t vt, vh;	// tail and head

	cin >> v;		// number of vertices
	g = graph_create(v);
	do {
		cin >> vt;
		cin >> c;
		cin >> vh;
		gol_insert(g, vt, vh);
		cin.get(c);
	} while (c == ',');

	graph_SCC_kosaraju(g);
	return 0;
}

// create a directed graph with N nodes and 0 edge
graph_d graph_create(const size_t N)
{
	graph_d g;
	size_t i;

	g.n = N;
	g.v = new graph_node[N];
	for (i = 0; i < N; ++i)
	{
		g.v[i].data = i + 'A';
		g.v[i].firstin = g.v[i].firstout = NULL;
	}
	return g;
}

// insert an edge
graph_d& gol_insert(graph_d& g, const size_t Tail, const size_t Head)
{
	gol_node* p;

	p = new  gol_node;
	p->tail = Tail;
	p->head = Head;
	p->tnext = g.v[Tail].firstout;
	p->hnext = g.v[Head].firstin;
	g.v[Tail].firstout = g.v[Head].firstin = p;
	return g;
}
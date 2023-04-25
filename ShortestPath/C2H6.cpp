#include "graph_d.h"

using namespace std;

int main()
{
	graph_d g;
	size_t nv, s;
	size_t vt, vh;	// tail and head
	char c;
	len_t w;
	size_t i;

	cin >> nv >> s;		// number of vertices and starting
	g = graph_create(nv);
	while (cin >> vt)
	{
		cin >> c >> vh >> w;
		g.v[vt].adjlist = gal_insert(g.v[vt].adjlist, vh, w);
	}
	shortestpath_dijkstra(g, s);
	for (i = 0; i < g.n; ++i)
	{
		if (len[i] < WINF)
			cout << g.v[i].data << ": " << path[i] << ", " << len[i] << endl;
		else
			cout << g.v[i].data << ": Infinity" << endl;
	}
	return 0;
}
// create an undirected graph with N nodes and 0 edge
graph_d graph_create(const size_t N)
{
	graph_d g;
	size_t i;

	g.n = N;
	g.v = new graph_node[N];
	for (i = 0; i < N; ++i)
	{
		g.v[i].data = 'A' + i;
		g.v[i].adjlist = NULL;
	}
	return g;
}

// insert a node in the adjacency list, whose head has SMALLEST tv_index
gal_node* gal_insert(gal_node* const F, const size_t N, const len_t Weight)
{
	gal_node* p, * q;

	p = new gal_node;
	p->tv_index = N;
	p->weight = Weight;
	if (F == NULL || N <= F->tv_index)
	{
		p->next = F;
		return p;
	}
	for (q = F; q->next != NULL && q->next->tv_index < N; q = q->next)
		;
	p->next = q->next;
	q->next = p;
	return F;
}
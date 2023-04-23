#include "graph_ud.h"

using namespace std;

int main()
{
	graph_ud g;
	tree_node* t;
	size_t v;
	char c;
	size_t vt, vh;	// tail and head

	cin >> v;		// number of vertices
	g = graph_create(v);
	do {
		cin >> vt;
		cin >> c;
		cin >> vh;
		g.v[vt].adjlist = gal_insert(g.v[vt].adjlist, vh);
		g.v[vh].adjlist = gal_insert(g.v[vh].adjlist, vt);
		cin.get(c);
	} while (c == ',');

	t = DFS_forest(g);
	tree_print(t);

	return 0;
}

// create an undirected graph with N nodes and 0 edge
graph_ud graph_create(const size_t N)
{
	graph_ud g;
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
gal_node* gal_insert(gal_node* const F, const size_t N)
{
	gal_node* p, * q;

	p = new gal_node;
	p->tv_index = N;
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
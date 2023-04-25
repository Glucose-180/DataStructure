#include "graph_d.h"

using namespace std;

int main()
{
	graph_d g;
	size_t nv;
	size_t vt, vh;
	dur_t dur;

	cin >> nv;	// number of vertices
	g = graph_create(nv);
	while (cin >> vt)
	{	// an edge: tail, head, duration
		cin >> vh >> dur;
		gol_insert(g, vt, vh, dur);
	}
	if (critical_path(g) == false)
		cerr << "**Error: not a DAG." << endl;
	return 0;
}

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
graph_d& gol_insert(graph_d& g, const size_t Tail, const size_t Head, const dur_t Duration)
{
	gol_node* p;

	p = new  gol_node;
	p->tail = Tail;
	p->head = Head;
	p->tnext = g.v[Tail].firstout;
	p->hnext = g.v[Head].firstin;
	p->duration = Duration;
	g.v[Tail].firstout = g.v[Head].firstin = p;
	return g;
}
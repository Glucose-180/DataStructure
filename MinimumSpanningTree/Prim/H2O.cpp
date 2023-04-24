#include "graph_ud.h"

using namespace std;

const char Inf = '$';	// input $ to represent infinity

int main()
{
	size_t n, i, j;
	graph_ud g;
	char c;

	cin >> n;	// number of vertices
	g = create_graph(n);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
		{
			cin >> g.adjmat[i * n + j];
			if (!cin)
			{
				cin.clear();
				cin >> c;
				if (c == Inf)
					g.adjmat[i * n + j] = WINF;
				else
				{
					g.adjmat[i * n + j] = 0.0F;
					cerr << "**Error: invalid input: " << c << endl;
				}
			}
		}
	cin >> n;	// starting vertex
	MST_prim(g, n);
	return 0;
}

// create an undirected graph with N nodes and 0 edge
graph_ud create_graph(const size_t N)
{
	graph_ud g;
	size_t i;

	g.vnum = N;
	g.data = new gnode_t[N];
	g.adjmat = new weight_t[N * N];
	for (i = 0; i < N; ++i)
		g.data[i] = 'A' + i;
	for (i = 0; i < N * N; ++i)
		g.adjmat[i] = WINF;
	return g;
}
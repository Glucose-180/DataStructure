#include <iostream>
#include <cstring>

using namespace std;

struct gal_node {
	size_t tv_index;	// index of terminal vertex
	gal_node* next;
};

struct graph_ud {	// undirected
	size_t n;		// number of vertices
	gal_node** v;
};

graph_ud g;
bool* flag_visited;

gal_node* gal_insert(gal_node* const F, const size_t N);
void graph_traverse_DFS(const graph_ud G, const size_t S);

int main()
{
	size_t v, i;
	char c;
	bool zero = false;
	size_t vt, vh;	// tail and head

	cin >> v;		// number of vertices
	g.n = v;
	g.v = new gal_node * [v];
	flag_visited = new bool[v];

	memset(g.v, 0, (v) * sizeof(gal_node*));
	memset(flag_visited, 0, (v) * sizeof(bool));

	do {
		cin >> vt;
		cin >> c;
		cin >> vh;
		g.v[vt] = gal_insert(g.v[vt], vh);
		g.v[vh] = gal_insert(g.v[vh], vt);
		cin.get(c);
	} while (c == ',');

	for (i = 0; i < g.n; ++i)
		if (flag_visited[i] == false)
		{
			graph_traverse_DFS(g, i);
			cout << endl;
		}
	return 0;
}

gal_node* gal_insert(gal_node* const F, const size_t N)
{
	gal_node* p, * q;

	p = new gal_node;
	p->tv_index = N;
	if (F == NULL || N >= F->tv_index)
	{
		p->next = F;
		return p;
	}
	for (q = F; q->next != NULL && q->next->tv_index > N; q = q->next)
		;
	p->next = q->next;
	q->next = p;
	return F;
}

void graph_traverse_DFS(const graph_ud G, const size_t S)
{
	gal_node* p;

	flag_visited[S] = true;
	cout << S << ',';
	for (p = G.v[S]; p != NULL; p = p->next)
	{
		if (flag_visited[p->tv_index] == false)
			graph_traverse_DFS(G, p->tv_index);
	}
}
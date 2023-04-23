#include "graph_ud.h"

static size_t* visited, * low;
static size_t ymr;
static bool* is_apoint;

static void DFS_artpoints(const graph_ud& G, const size_t S);
static inline size_t umin(size_t x, size_t y);

// find all articulation points of CONNECTED undirected graph G
void find_artpoints(const graph_ud& G)
{
	gal_node* p;
	size_t v;

	if ((p = G.v[0].adjlist) == NULL)
		return;
	visited = new size_t[G.n];
	low = new size_t[G.n];
	is_apoint = new bool[G.n];
	memset(visited, 0, G.n * sizeof(size_t));
	memset(visited, 0, G.n * sizeof(size_t));
	memset(is_apoint, 0, G.n * sizeof(bool));
	visited[0] = ymr = 1;
	DFS_artpoints(G, p->tv_index);
	if (ymr < G.n)
	{
		//std::cout << G.v[0].data;
		is_apoint[0] = true;
		for (p = p->next; p != NULL; p = p->next)
		{
			v = p->tv_index;
			if (visited[v] == 0)
				DFS_artpoints(G, v);
		}
	}
	for (v = 0; v < G.n; ++v)
		if (is_apoint[v] == true)
			std::cout << G.v[v].data;
	std::cout << std::endl;
	delete[] visited;
	delete[] low;
	delete[] is_apoint;
}

// do DFS starting from vertex S
static void DFS_artpoints(const graph_ud& G, const size_t S)
{
	size_t min;
	gal_node* p;

	visited[S] = min = ++ymr;
	for (p = G.v[S].adjlist; p != NULL; p = p->next)
	{
		size_t av = p->tv_index;
		if (visited[av] == 0)
		{
			DFS_artpoints(G, av);
			min = umin(min, low[av]);
			if (low[av] >= visited[S])
				//std::cout << G.v[S].data;
				is_apoint[S] = true;
		}
		else
			min = umin(min, visited[av]);
	}
	low[S] = min;
}

static inline size_t umin(size_t x, size_t y)
{
	if (x < y)
		return x;
	else
		return y;
}
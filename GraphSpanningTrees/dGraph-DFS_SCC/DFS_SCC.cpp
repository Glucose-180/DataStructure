#include "graph_d.h"

static bool* flag_visited;
static size_t* stack_finished;
static size_t sp;	// stack pointer

static void graph_traverse_DFS(const graph_d& G, const size_t S);
static void graph_traverse_rDFS(const graph_d& G, const size_t S);

// print SCC of directed graph G using Kosaraju's algorithm
void graph_SCC_kosaraju(const graph_d& G)
{
	size_t i;
	size_t v;

	flag_visited = new bool[G.n];
	stack_finished = new size_t[G.n];
	sp = 0;
	memset(flag_visited, 0, G.n * sizeof(bool));
	for (i = 0; i < G.n; ++i)
	{
		if (flag_visited[i] == false)
			graph_traverse_DFS(G, i);
	}
	memset(flag_visited, 0, G.n * sizeof(bool));
	while (sp > 0U)
	{
		v = stack_finished[--sp];
		if (flag_visited[v] == true)
			continue;
		graph_traverse_rDFS(G, v);
		std::cout << std::endl;
	}
	delete[] flag_visited;
	delete[] stack_finished;
}

// traverse a directed graph G starting from S, using DFS and push vertices into stack
static void graph_traverse_DFS(const graph_d& G, const size_t S)
{
	gol_node* p;

	flag_visited[S] = true;
	for (p = G.v[S].firstout; p != NULL; p = p->tnext)
	{
		if (flag_visited[p->head] == true)
			continue;
		graph_traverse_DFS(G, p->head);
	}
	stack_finished[sp++] = S;
}

// traverse a directed graph G REVERSELY starting from S, using DFS and print
static void graph_traverse_rDFS(const graph_d& G, const size_t S)
{
	gol_node* p;

	flag_visited[S] = true;
	std::cout << G.v[S].data;
	for (p = G.v[S].firstin; p != NULL; p = p->hnext)
	{
		if (flag_visited[p->tail] == true)
			continue;
		graph_traverse_rDFS(G, p->tail);
	}
}
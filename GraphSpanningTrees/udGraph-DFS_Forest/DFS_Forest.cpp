#include "graph_ud.h"

static bool* flag_visited;

static void DFS_tree(const graph_ud G, const size_t S, tree_node* const R);

// create spanning forest of graph G using DFS
tree_node* DFS_forest(const graph_ud G)
{
	tree_node* root = NULL, * p, * q = NULL;
	size_t i;

	flag_visited = new bool[G.n];
	memset(flag_visited, 0, G.n * sizeof(bool));
	for (i = 0; i < G.n; ++i)
	{
		if (flag_visited[i] == true)
			continue;
		p = new tree_node;
		p->data = G.v[i].data;
		p->firstchild = p->nextsibling = NULL;
		if (root == NULL)
			root = p;
		else
			q->nextsibling = p;
		q = p;
		DFS_tree(G, i, q);
	}
	delete[] flag_visited;
	return root;
}

// create spanning tree, whose root is R, of graph G, starting from vertex S
static void DFS_tree(const graph_ud G, const size_t S, tree_node* const R)
{
	bool flag_first = true;
	gal_node* u;
	tree_node* p, *q = NULL;

	flag_visited[S] = true;
	for (u = G.v[S].adjlist; u != NULL; u = u->next)
	{
		if (flag_visited[u->tv_index] == true)
			continue;
		p = new tree_node;
		p->data = G.v[u->tv_index].data;
		p->firstchild = p->nextsibling = NULL;
		if (flag_first == true)
		{
			R->firstchild = p;
			flag_first = false;
		}
		else
			q->nextsibling = p;
		q = p;
		DFS_tree(G, u->tv_index, q);
	}
}

// print a tree using concave table
void tree_print(tree_node* const T, const int Level)
{
	tree_node* p;
	int i;

	for (p = T; p != NULL; p = p->nextsibling)
	{
		for (i = 0; i < Level; ++i)
			putchar('-');
		putchar(p->data);
		putchar('\n');
		if (p->firstchild != NULL)
			tree_print(p->firstchild, Level + 1);
	}
}
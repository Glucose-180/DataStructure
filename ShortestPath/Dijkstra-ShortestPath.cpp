#include "graph_d.h"

using std::string;

string* path;
len_t* len;

void shortestpath_dijkstra(const graph_d& G, const size_t S)
{
	bool* flag_done = new bool[G.n];
	size_t* last_renewer = new size_t[G.n];
	size_t i, u, v;
	gal_node* p;

	path = new string[G.n];
	len = new len_t[G.n];
	for (i = 0; i < G.n; ++i)
	{
		len[i] = WINF;
		flag_done[i] = false;
		path[i] = "";
	}
	len[S] = 0;
	path[S] += G.v[S].data;
	while (true)
	{
		for (i = 0; i < G.n; ++i)
			if (flag_done[i] == false)
				break;
		if (i == G.n)
			break;		// done
		{	// find minimum length
			len_t min;
			u = i, min = len[i];
			for (; i < G.n; ++i)
				if (flag_done[i] == false && len[i] < min)
					u = i, min = len[i];
		}
		if (u != S && len[u] < WINF)
			path[u] = path[last_renewer[u]] + G.v[u].data;	// renew path
		flag_done[u] = true;
		for (p = G.v[u].adjlist; p != NULL; p = p->next)
		{
			if (flag_done[v = p->tv_index] == true)
				continue;
			if (len[u] + p->weight < len[v])
			{
				len[v] = len[u] + p->weight;
				last_renewer[v] = u;
			}
		}
	}
	delete[] last_renewer;
	delete[] flag_done;
}
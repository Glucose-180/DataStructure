#include <iostream>
#include <cstring>

using namespace std;

struct gal_node {
	size_t tv_index;	// index of terminal vertex
	gal_node* next;
};

struct graph_d {	// directed
	size_t n;		// number of vertices
	gal_node** v;
};

graph_d g;
size_t* queue_BFS;
size_t q_head, q_tail;

gal_node* gal_insert(gal_node* const F, const size_t N);
void graph_traverse_BFS(const graph_d G, const size_t S);

int main()
{
	size_t v, i, j;
	char c;
	bool zero = false;
	size_t vt, vh;	// tail and head

	cin >> v;		// number of vertices
	g.n = v;
	g.v = new gal_node * [v];

	queue_BFS = new size_t[v];

	memset(g.v, 0, (v) * sizeof(gal_node*));
	memset(queue_BFS, 0, v);
	q_head = q_tail = 0;

	do {
		cin >> vt;
		cin >> c;
		cin >> vh;
		g.v[vt] = gal_insert(g.v[vt], vh);
		cin.get(c);
	} while (c == ',');

	for (j = 0; j < g.n; ++j)
	{
		for (i = 0; i < q_tail; ++i)
			if (queue_BFS[i] == j)
				break;
		if (i >= q_tail)
		{
			graph_traverse_BFS(g, j);
			cout << endl;
		}
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

void graph_traverse_BFS(const graph_d G, const size_t S)
{
	size_t t, i;
	gal_node* p;

	queue_BFS[q_tail++] = S;	// enter
	while (q_head < q_tail)		// not empty
	{
		t = queue_BFS[q_head++];//depart
		cout << t << ',';
		for (p = G.v[t]; p != NULL; p = p->next)
		{
			for (i = 0; i < q_tail; ++i)
				if (queue_BFS[i] == p->tv_index)
					break;
			if (i >= q_tail)
				queue_BFS[q_tail++] = p->tv_index;
		}
	}
}
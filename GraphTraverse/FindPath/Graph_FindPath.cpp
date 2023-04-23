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

struct step_t {		// step in queue
	size_t cur;
	size_t last;
};

graph_ud g;
bool* flag_visited;

gal_node* gal_insert(gal_node* const F, const size_t N);
bool graph_findpath_DFS(const graph_ud G, const size_t S, const size_t T);
bool graph_findpath_BFS(const graph_ud G, const size_t S, const size_t T);

int main()
{
	size_t v, start, terminal;
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
	cin >> start >> terminal;

	cout << "DFS: ";
	if (graph_findpath_DFS(g, start, terminal) == false)
		cout << "No path.";
	cout << endl;
	cout << "BFS: ";
	if (graph_findpath_BFS(g, start, terminal) == false)
		cout << "No path.";
	cout << endl;
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

bool graph_findpath_DFS(const graph_ud G, const size_t S, const size_t T)
{
	gal_node* p;

	flag_visited[S] = true;
	if (S == T)
	{
		cout << S << ',';
		return true;
	}
	for (p = G.v[S]; p != NULL; p=p->next)
		if (flag_visited[p->tv_index] == false && graph_findpath_DFS(G, p->tv_index, T) == true)
		{
			cout << S << ',';
			return true;
		}
	return false;
}

bool graph_findpath_BFS(const graph_ud G, const size_t S, const size_t T)
{
	step_t* queue_BFS = new step_t[G.n];
	step_t qtemp;
	size_t head = 0, tail = 0;
	size_t i;
	gal_node* p;

	queue_BFS[tail].cur = S;
	queue_BFS[tail].last = 0;
	++tail;		// enter

	while (head < tail)
	{
		qtemp = queue_BFS[head++];
		if (T == qtemp.cur)
		{		// found
			i = head - 1;
			do {
				cout << queue_BFS[i].cur << ',';
			} while (i > 0 && ((i = queue_BFS[i].last) || true));
			delete[] queue_BFS;
			return true;
		}
		for (p = G.v[qtemp.cur]; p != NULL; p = p->next)
		{
			for (i = 0; i < tail; ++i)
				if (queue_BFS[i].cur == p->tv_index)
					break;
			if (i >= tail)
			{
				queue_BFS[tail].cur = p->tv_index;
				queue_BFS[tail].last = head - 1;
				++tail;
			}
		}
	}
	delete[] queue_BFS;
	return false;
}
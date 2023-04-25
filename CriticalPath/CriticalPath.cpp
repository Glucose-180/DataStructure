#include "graph_d.h"

static size_t* tpl_order;
static dur_t* v_earliest, * v_latest;

static bool tpl_sort(const graph_d& G);
static unsigned int* get_indegree(const graph_d& G);
static inline dur_t umax(const dur_t X, const dur_t Y);
static inline dur_t umin(const dur_t X, const dur_t Y);

bool critical_path(const graph_d& G)
{
	size_t i, j;
	size_t end;		// the end vertex, or last activity
	dur_t e_earliest, e_latest;	// for edges, or activities
	gol_node* p;

	tpl_order = new size_t[G.n];
	v_earliest = new dur_t[G.n];
	v_latest = new dur_t[G.n];
	if (tpl_sort(G) == false)
	{
		delete[] tpl_order;
		delete[] v_earliest;
		delete[] v_latest;
		return false;		// circuit exists, not DAG!
	}
	end = tpl_order[G.n - 1];
	// initialize v_latest
	for (i = 0; i < G.n; ++i)
		v_latest[i] = v_earliest[end];
	while (i > 0)
	{
		j = tpl_order[--i];
		for (p = G.v[j].firstout; p != NULL; p = p->tnext)
			v_latest[j] = umin(v_latest[j], v_latest[p->head] - p->duration);
	}
	// recognize critical path
	for (i = 0; i < G.n; ++i)
		for (p = G.v[i].firstout; p != NULL; p = p->tnext)
		{
			e_earliest = v_earliest[i];
			e_latest = v_latest[p->head] - p->duration;
			if (e_earliest == e_latest)
				std::cout << G.v[i].data << "->" << G.v[p->head].data << ',';
			// get a critical activity
		}
	delete[] tpl_order;
	delete[] v_earliest;
	delete[] v_latest;
	return true;
}

// do Topological Sort and get v_earliest
static bool tpl_sort(const graph_d& G)
{
	unsigned int* indeg;
	size_t* indeg0, sp;		// stack of vertices with 0 in-degree
	size_t ymr;				// count
	size_t i, j;
	gol_node* p;

	indeg = get_indegree(G);
	indeg0 = new size_t[G.n];
	sp = 0;
	// let all 0-indeg vertices enter the stack
	// and initialize v_earliest
	for (i = 0; i < G.n; ++i)
	{
		if (indeg[i] == 0)
			indeg0[sp++] = i;
		v_earliest[i] = 0;
	}

	ymr = 0;
	while (sp > 0)
	{
		i = indeg0[--sp];	// get out of the stack
		tpl_order[ymr++] = i;
		for (p = G.v[i].firstout; p != NULL; p = p->tnext)
		{
			j = p->head;
			if (--indeg[j] == 0)
				indeg0[sp++] = j;	// new 0-indeg vertex
			v_earliest[j] = umax(v_earliest[j], v_earliest[i] + p->duration);
		}
	}
	delete[] indeg;
	delete[] indeg0;
	if (ymr < G.n)
		return false;	// a circuit is detected!
	else
		return true;
}

static unsigned int* get_indegree(const graph_d& G)
{
	unsigned int* indeg, ymr;
	size_t i;
	gol_node* p;

	indeg = new unsigned int[G.n];
	for (i = 0; i < G.n; ++i)
	{
		ymr = 0;
		for (p = G.v[i].firstin; p != NULL; p = p->hnext)
			++ymr;
		indeg[i] = ymr;
	}
	return indeg;
}

static inline dur_t umax(const dur_t X, const dur_t Y)
{
	if (X > Y)
		return X;
	else
		return Y;
}

static inline dur_t umin(const dur_t X, const dur_t Y)
{
	if (X < Y)
		return X;
	else
		return Y;
}
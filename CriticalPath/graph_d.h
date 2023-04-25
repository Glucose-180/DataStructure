#ifndef __GRAPH_D__
#define __GRAPH_D__

#include <iostream>
#include <cstring>

typedef char gnode_t;
typedef unsigned int dur_t;	// duration type

// Orthogonal linked list
struct gol_node {
	size_t tail, head;
	gol_node* tnext, * hnext;
	dur_t duration;
};

struct graph_node {
	gnode_t data;
	gol_node* firstout, * firstin;
};

struct graph_d {	// directed graph
	size_t n;		// number of vertices
	graph_node* v;	// vertices
};

graph_d graph_create(const size_t N);
graph_d& gol_insert(graph_d& g, const size_t Tail, const size_t Head, const dur_t Duration);

bool critical_path(const graph_d& G);
#endif

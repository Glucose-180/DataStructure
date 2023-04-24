#ifndef __GRAPH_UD_H__
#define __GRAPH_UD_H__

#include <iostream>

typedef char gnode_t;
typedef unsigned int weight_t;

struct edge_t {
	size_t t1, t2;
	weight_t weight;
};

struct graph_ud {
	size_t vn, en;	// number of vertices, edges
	gnode_t* vl;	// vertex list
	edge_t* el;		// edge list
};

graph_ud create_graph(const size_t VN, const size_t EN);

void MST_kruskal(const graph_ud& G);

#endif
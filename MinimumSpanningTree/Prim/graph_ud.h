#ifndef __GRAPH_UD_H__
#define __GRAPH_UD_H__

#include <cmath>
#include <iostream>

#define WINF INFINITY	// infinite weight
#define WINU NAN		// weight representing that the vertex is already in tree

typedef char gnode_t;
typedef float weight_t;

struct graph_ud {
	size_t vnum;		// number of vertices
	gnode_t* data;
	weight_t* adjmat;	// adjacent matrix with weights
};


graph_ud create_graph(const size_t N);
void MST_prim(const graph_ud& G, const size_t S);

#endif
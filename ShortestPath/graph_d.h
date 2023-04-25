#ifndef __GRAPH_D_H__
#define __GRAPH_D_H__

#include <iostream>
#include <string>
#include <cmath>

#define WINF INFINITY

typedef char gnode_t;
typedef float len_t;

struct gal_node {
	size_t tv_index;	// index of terminal vertex
	gal_node* next;
	len_t weight;
};

struct graph_node {
	gnode_t data;
	gal_node* adjlist;
};

struct graph_d {	// directed
	size_t n;		// number of vertices
	graph_node* v;
};


extern std::string* path;
extern len_t* len;

graph_d graph_create(const size_t N);
gal_node* gal_insert(gal_node* const F, const size_t N, const len_t Weight);

void shortestpath_dijkstra(const graph_d& G, const size_t S);

#endif
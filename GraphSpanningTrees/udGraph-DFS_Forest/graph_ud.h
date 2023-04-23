#ifndef __GRAPH_UD_H__
#define __GRAPH_UD_H__

#include <iostream>
#include <cstring>

typedef char gnode_t;

struct gal_node {
	size_t tv_index;	// index of terminal vertex
	gal_node* next;
};

struct graph_node {
	gnode_t data;
	gal_node* adjlist;
};

struct graph_ud {	// undirected
	size_t n;		// number of vertices
	graph_node* v;
};

struct tree_node {	// spanning forest: child-sibling tree
	gnode_t data;
	tree_node* firstchild, * nextsibling;
};

graph_ud graph_create(const size_t N);
gal_node* gal_insert(gal_node* const F, const size_t N);

tree_node* DFS_forest(const graph_ud G);
void tree_print(tree_node* const T, const int Level = 0);
#endif
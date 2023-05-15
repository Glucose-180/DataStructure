#ifndef __NOSTREE_H__
#define __NOSTREE_H__

#include <iostream>
#include <cmath>

typedef int data_t;
typedef float weight_t;

#define WINF INFINITY

struct treenode {
	data_t data;
	treenode* left, * right;
};

treenode* generate_NOST(const data_t* const R, weight_t* const W, const int N);
treenode* search(treenode* const T, const data_t K);

#endif
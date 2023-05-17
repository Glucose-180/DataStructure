#ifndef __BST_H__
#define __BST_H__

#include <iostream>
typedef int data_t;

struct treenode {
	data_t data;
	treenode* left, * right;
};

treenode* BST_add_node(treenode* const T, const data_t D);
bool BST_search(treenode* const T, const data_t D, treenode*& rp, treenode*& rt);
void BST_print(const treenode* const T, bool concave, const char* const Tab = "\t", const unsigned int Level = 0U);
treenode* BST_delete_node(treenode* const T, const data_t D);

#endif
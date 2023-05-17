#include "BST.h"

static inline int BST_cmp(const data_t D1, const data_t D2)
{
	if (D1 == D2)
		return 0;
	else if (D1 < D2)
		return -1;
	else
		return 1;
}

treenode* BST_add_node(treenode* const T, const data_t D)
{
	treenode* p = T, * q;
	int crt;

	while (p != NULL)
	{
		crt = BST_cmp(D, p->data);
		if (crt == 0)
			return T;	// D already exists
		else if (crt > 0)	// D > p->data
			if (p->right != NULL)
				p = p->right;
			else
				break;
		else
			if (p->left != NULL)
				p = p->left;
			else
				break;
	}
	q = new treenode;
	q->data = D;
	q->left = q->right = NULL;
	if (p == NULL)	// T is NULL
		return q;
	if (crt > 0)
		p->right = q;
	else
		p->left = q;
	return T;
}

/* Search D in BST T.
If D is found, then rt points to it and rp points to its parent;
otherwise, rp points to the last node before failed and return false.
Note: rp will be set NULL if D is the root. */
bool BST_search(treenode* const T, const data_t D, treenode*& rp, treenode*& rt)
{
	int crt;

	rp = NULL;
	rt = T;
	while (rt != NULL)
	{
		crt = BST_cmp(D, rt->data);
		if (crt == 0)
			return true;
		rp = rt;
		if (crt > 0)
			rt = rt->right;
		else
			rt = rt->left;
	}
	return false;
}

/* Print a BST.
If concave is true, then use concave table;
otherwise, use inorder traverse. */
void BST_print(const treenode* const T, bool concave, const char* const Tab, const unsigned int Level)
{
	unsigned int i;

	if (T == NULL)
		return;
	if (concave == true)
	{
		for (i = 0; i < Level; ++i)
			std::cout << Tab;
		std::cout << T->data << std::endl;
		if (T->left == NULL && T->right != NULL)
		{
			for (i = 0; i <= Level; ++i)
				std::cout << Tab;
			std::cout << std::endl;
		}
		else
			BST_print(T->left, true, Tab, Level + 1);
		BST_print(T->right, true, Tab, Level + 1);
	}
	else
	{
		BST_print(T->left, false, Tab, Level + 1);
		std::cout << T->data << Tab;
		BST_print(T->right, false, Tab, Level + 1);
		if (Level == 0U)
			std::cout << std::endl;
	}
}

/* Delete node D in BST T. */
treenode* BST_delete_node(treenode* const T, const data_t D)
{
	treenode* f, * p, * s;

	if (BST_search(T, D, f, p) == false || p == NULL)
		return T;	// not found
	if (p->left != NULL && p->right != NULL)
	{
		s = p->right;
		f = p;
		while (s->left != NULL)
		{	// find the adjacent next node of p
			f = s;
			s = s->left;
		}
		p->data = s->data;
		p = s;
		// now p points to the real node to be deleted
		// and f points to the parent of p
	}
	// now p cannot have two children
	if (p->left != NULL)
		s = p->left;
	else
		s = p->right;
	// s points to the only child of p or NULL
	if (f == NULL)
	{	// p is actually the root
		delete p;
		return s;
	}
	else
	{	// hang s on f
		if (BST_cmp(p->data, f->data) < 0)
			f->left = s;
		else
			f->right = s;
		delete p;
		return T;
	}
}
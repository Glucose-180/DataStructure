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
			return NULL;	// D already exists
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
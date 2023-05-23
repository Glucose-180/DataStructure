/* balance.c: 用于对平衡二叉树做平衡化旋转处理；
* 每个函数接受一个指向待操作子树的根节点的指针，
* 返回指向操作后的根节点的指针。*/
#include "BBST.h"

/* 对以 R 为根的子树做左单旋转 */
BBST_node* rotate_L(BBST_node* const R)
{
	BBST_node* rc;

	rc = R->right;
	R->right = rc->left;
	rc->left = R;
	return rc;
}

/* 对以 R 为根的子树做右单旋转 */
BBST_node* rotate_R(BBST_node* const R)
{
	BBST_node* lc;

	lc = R->left;
	R->left = lc->right;
	lc->right = R;
	return lc;
}

/* 对以 R 为根的子树做左右双旋 */
BBST_node* rotate_LR(BBST_node* const R)
{
	BBST_node* lc, * rc;
	BBST_node* p;	/* 指向新的根 */

	lc = R->left;
	rc = R;
	p = lc->right;

	lc->right = p->left;
	p->left = lc;
	rc->left = p->right;
	p->right = rc;

	return p;
}

BBST_node* rotate_RL(BBST_node* const R)
{
	BBST_node* lc, * rc;
	BBST_node* p;	/* 指向新的根 */

	lc = R;
	rc = R->right;
	p = rc->left;

	rc->left = p->right;
	p->right = rc;
	lc->right = p->left;
	p->left = lc;
	
	return p;
}


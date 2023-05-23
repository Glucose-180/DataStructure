/* balance.c: 用于对平衡二叉树做平衡化旋转处理；
* 每个函数接受一个指向待操作子树的根节点的指针，
* 返回指向操作后的根节点的指针。*/
#include "BBST.h"

/* 对以 R 为根的子树做左单旋转 */
static BBST_node* rotate_L(BBST_node* const R)
{
	BBST_node* rc;

	rc = R->right;
	R->right = rc->left;
	rc->left = R;
	return rc;
}

/* 对以 R 为根的子树做右单旋转 */
static BBST_node* rotate_R(BBST_node* const R)
{
	BBST_node* lc;

	lc = R->left;
	R->left = lc->right;
	lc->right = R;
	return lc;
}

/* 对以 R 为根的子树做左右双旋 */
static BBST_node* rotate_LR(BBST_node* const R)
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

/* 对以 R 为根的子树做右左双旋 */
static BBST_node* rotate_RL(BBST_node* const R)
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

/* 对以 R 为根的子树做左平衡旋转 */
/* 用于某一新结点挂在了 R 的左子树上导致的不平衡 */
BBST_node* balance_L(BBST_node* const R)
{
	BBST_node* lc, * lrc;
	BBST_node* p = NULL;	/* 指向新的根 */

	lc = R->left;	/* 指向 R 的左子树 */
	switch (lc->bf)
	{
	case LT:
		/* 新结点挂在了 lc 的左子树上 */
		R->bf = lc->bf = ET;
		p = rotate_R(R);	/* 右单旋 */
		break;
	case RT:
		/* 新结点挂在了 lc 的右子树上 */
		lrc = lc->right;	/* R 的左孩子的右孩子 */
		switch (lrc->bf)
		{	/* 修改 R, lc, lrc 的平衡因子 */
		case LT:
			R->bf = RT;
			lc->bf = ET;
			break;
		case ET:
			R->bf = lc->bf = ET;
			break;
		case RT:
			R->bf = ET;
			lc->bf = LT;
			break;
		}
		lrc->bf = ET;
		p = rotate_LR(R);	/* 左右双旋 */
		break;
	}
	return p;
}

/* 对以 R 为根的子树做右平衡旋转 */
/* 用于某一新结点挂在了 R 的右子树上导致的不平衡 */
BBST_node* balance_R(BBST_node* const R)
{
	BBST_node* rc, * rlc;
	BBST_node* p = NULL;	/* 指向新的根 */

	rc = R->right;	/* 指向 R 的右子树 */
	switch (rc->bf)
	{
	case RT:
		/* 新结点挂在了 rc 的右子树上 */
		R->bf = rc->bf = ET;
		p = rotate_L(R);	/* 左单旋 */
		break;
	case LT:
		/* 新结点挂在了 rc 的右子树上 */
		rlc = rc->left;	/* R 的右孩子的左孩子 */
		switch (rlc->bf)
		{	/* 修改 R, rc, rlc 的平衡因子 */
		case RT:
			R->bf = LT;
			rc->bf = ET;
			break;
		case ET:
			R->bf = rc->bf = ET;
			break;
		case LT:
			R->bf = ET;
			rc->bf = RT;
			break;
		}
		rlc->bf = ET;
		p = rotate_RL(R);	/* 右左双旋 */
		break;
	}
	return p;
}
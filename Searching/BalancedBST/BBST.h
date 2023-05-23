#ifndef __BBST_H__
#define __BBST_H__

/* 数据类型 */
typedef int data_t;

/* 平衡因子：左子树更高，左右子树等高，右子树更高。 */
enum Balanced_factor { LT = 1, ET = 0, RT = -1 };

/* 平衡二叉树的结点 */
typedef struct BBST_node {
	data_t data;
	enum Balanced_factor bf;
	struct BBST_node* left, * right;
} BBST_node;

#endif
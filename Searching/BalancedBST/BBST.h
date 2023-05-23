#ifndef __BBST_H__
#define __BBST_H__

#ifndef NULL	/* 空指针 */
#define NULL ((void *)0)
#endif

/* 数据类型 */
typedef int data_t;

/* 平衡因子：左子树更高，左右子树等高，右子树更高。 */
enum Balanced_factor { LT = 1, ET = 0, RT = -1 };

/* 布尔类型的变量 */
typedef enum Boolean { False, True } bool_t;

/* 平衡二叉树的结点 */
typedef struct BBST_node {
	data_t data;
	enum Balanced_factor bf;
	struct BBST_node* left, * right;
} BBST_node;

/* BBST_search 函数的返回类型 */
typedef struct BBST_srt_t {
	BBST_node* tar,	/* 指向待搜索的目标结点 */
		* par;	/* 指向其父母 */
	BBST_node** path;	/* 从根结点到目标结点的路径，以 NULL 结尾。 */
} BBST_srt_t;

extern unsigned int BBST_ymr;

BBST_node* balance_L(BBST_node* const R);
BBST_node* balance_R(BBST_node* const R);

/* 通用的数据比较函数，用于适应多种数据类型。
* 若 X 小于 Y，则返回负值；若二者相等则返回 0；否则返回正值。 */
static inline int dt_comp(const data_t X, const data_t Y)
{
	if (X < Y)
		return -1;
	else if (X == Y)
		return 0;
	else
		return 1;
}

BBST_node* BBST_insert(BBST_node* const R, const data_t D);
BBST_srt_t BBST_search(BBST_node* const T, const data_t D);
unsigned int BBST_get_max_depth(void);

#endif
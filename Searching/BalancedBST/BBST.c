#include <stdlib.h>
#include "BBST.h"

/* 子树“长高”标志，仅供 BBST_insert 函数使用！ */
static bool_t flag_taller;

/* 将数据 D 插入以 R 为根的树中，
* 设置 flag_taller 变量并返回指向新的根的指针。 
* 如果该树“长高”了，则 flag_taller 会被置为 True，否则为 False。
* 但如果新建结点失败，则会返回空指针 NULL。 */
BBST_node* BBST_insert(BBST_node* const R, const data_t D)
{
	BBST_node* p;	/* 指向新的根 */

	if (R == NULL)
	{
		p = (BBST_node*)malloc(sizeof(BBST_node));
		if (p == NULL)
			return NULL;	/* 新建结点失败 */
		p->data = D;
		p->left = p->right = NULL;
		p->bf = ET;
		flag_taller = True;
	}
	else
	{
		int crt = dt_comp(D, R->data);
		if (crt == 0)
		{	/* 数据 D 已经存在 */
			flag_taller = False;
			p = R;
		}
		else if (crt < 0)
		{	/* 将 D 挂在 R 的左子树 */
			if ((R->left = BBST_insert(R->left, D)) == NULL)
				p = NULL;
			else
				if (flag_taller == True)
				{	/* 左子树“长高”了 */
					switch (R->bf)
					{	/* 检查 R （原来的）平衡因子 */
					case LT:
						/* 原来左子树高，需做左平衡 */
						p = balance_L(R);
						flag_taller = False;
						break;
					case ET:
						/* 原来二子树等高，插入使左子树更高 */
						R->bf = LT;
						flag_taller = True;
						p = R;
						break;
					case RT:
						/* 原来右子树高，插入使二子树等高 */
						R->bf = ET;
						flag_taller = False;
						p = R;
						break;
					}
				}
				else
					p = R;
		}
		else
		{	/* 将 D 挂在 R 的右子树上 */
			if ((R->right = BBST_insert(R->right, D)) == NULL)
				p = NULL;
			else
				if (flag_taller == True)
				{	/* 右子树“长高”了 */
					switch (R->bf)
					{	/* 检查 R （原来的）平衡因子 */
					case RT:
						/* 原来右子树高，需做右平衡 */
						p = balance_R(R);
						flag_taller = False;
						break;
					case ET:
						/* 原来二子树等高，插入使右子树更高 */
						R->bf = RT;
						flag_taller = True;
						p = R;
						break;
					case LT:
						/* 原来左子树高，插入使二子树等高 */
						R->bf = ET;
						flag_taller = False;
						p = R;
						break;
					}
				}
				else
					p = R;
		}
	}
	return p;
}
#include <stdlib.h>
#include "BBST.h"

/* 子树“长高”标志，仅供 BBST_insert 函数使用！ */
static bool_t flag_taller;

/* 统计树中结点的总数 */
unsigned int BBST_ymr;

/* 将数据 D 插入以 R 为根的树中，
* 设置 flag_taller 变量并返回指向新的根的指针。 
* 如果该树“长高”了，则 flag_taller 会被置为 True，否则为 False。
* 但如果新建结点失败，则会返回空指针 NULL。 */
BBST_node* BBST_insert(BBST_node* const R, const data_t D)
{
	BBST_node* p = NULL;	/* 指向新的根 */

	if (R == NULL)
	{
		p = (BBST_node*)malloc(sizeof(BBST_node));
		if (p == NULL)
			return NULL;	/* 新建结点失败 */
		p->data = D;
		p->left = p->right = NULL;
		p->bf = ET;
		flag_taller = True;
		++BBST_ymr;
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

/* 在以 T 为根的树中搜索数据 D。
* 如果找到，那么返回的 tar 指向目标结点，par 指向其父母；
* 否则，par 指向搜索失败前访问的最后一个结点，tar 为 NULL。
* 注意：如果目标结点恰好是根，那么 par 为 NULL。*/
BBST_srt_t BBST_search(BBST_node* const T, const data_t D)
{
	int crt;
	BBST_srt_t srt = { NULL,NULL,NULL };

	static BBST_node** path = NULL;
	static unsigned int cur_size = 0U, new_size;
	unsigned int i = 0U;

	srt.tar = T;

	new_size = BBST_get_max_depth() + 1U;
	if (path != NULL && cur_size < new_size)
		free(path);
	if (new_size > cur_size)
	{
		path = (BBST_node**)malloc(new_size * sizeof(BBST_node*));
		cur_size = new_size;
	}

	while (path != NULL && (path[i++] = srt.tar) != NULL || srt.tar != NULL)
	{
		crt = dt_comp(D, srt.tar->data);
		if (crt == 0)
		{
			if (path != NULL)
				path[i] = NULL;
			break;
		}
		srt.par = srt.tar;
		if (crt > 0)
			srt.tar = srt.tar->right;
		else
			srt.tar = srt.tar->left;
	}
	srt.path = path;
	return srt;
}

/* 根据结点数，获取平衡二叉树的最大深度 */
unsigned int BBST_get_max_depth()
{
	/* 可用数学方法进行优化，暂时取一个固定值。 */
	return 15U;
}
#include <stdlib.h>
#include "BBST.h"

/* 子树“长高”标志，仅供 BBST_insert 函数使用！ */
static bool_t flag_taller;

/* 子树“缩短”标志，仅供 BBST_delete 函数使用！ */
static enum { LS = 1, RS = 0, NS = -1, UC = 2 } flag_shorter;
/* LS, RS 分别表示左、右子树缩短，
* NS，UC 分别表示没有缩短和缩短了但具体是谁不重要。*/

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
* 注意：如果目标结点恰好是根，那么 par 为 NULL。
* 此外，path 指向从根到目标结点的路径，以 NULL 结束，
* 若搜索失败，则是从根到 par 的路径。*/
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

/* 在以 R 为根的树上删除数据 D 所在的结点，
* 返回指向新的根的指针。*/
BBST_node* BBST_delete(BBST_node* const R, const data_t D)
{
	BBST_srt_t srt;
	int i;
	BBST_node* p, * q;
	/* rt 用于接收返回值。 */
	BBST_node* rt;

	srt = BBST_search(R, D);
	if (srt.tar == NULL)
	{	/* 未找到目标结点 */
		flag_shorter = NS;
		return R;
	}
	for (i = 0; srt.path[i] != NULL; ++i)
		;

	if (srt.tar->left != NULL && srt.tar->right != NULL)
	{	/* 若目标结点有两个孩子，则需寻找它的直接前驱 */
		BBST_node* temp = srt.tar->left;
		srt.path[i++] = temp;
		while (temp->right != NULL)
		{
			temp = temp->right;
			/* 补充从根到目标结点的路径 */
			srt.path[i++] = temp;
		}
		srt.path[i] = NULL;
		/* 将直接前驱的数据传给目标结点 */
		srt.tar->data = temp->data;
		/* tar 指向直接前驱，成为要删除的结点 */
		srt.tar = temp;
	}
	/* 至此，tar 至多有一个孩子，并且 path 中是从根到它的路径 */
	if (srt.tar == R)
	{	/* 要删除根节点，则直接返回其子树 */
		BBST_node* temp;
		if (R->left != NULL)
			temp = R->left;
		else
			temp = R->right;
		free(R);
		return temp;
	}
	--i;
	p = srt.path[--i];	/* tar 的父母 */

	/* 将 tar 唯一的子树挂在 p 上 */
	if (p->left == srt.tar)
	{
		p->left = (srt.tar->left != NULL ? srt.tar->left : srt.tar->right);
		flag_shorter = LS;	/* 设置子树缩短标志 */
	}
	else
	{
		p->right = (srt.tar->left != NULL ? srt.tar->left : srt.tar->right);
		flag_shorter = RS;
	}
	free(srt.tar);
	//rt = R;

	while (flag_shorter != NS && i >= 0)
	{	/* 到此，flag_shorter 指示 p 的哪个子树缩短了 */
		/* tf 指向 p 的父母，如果没有则为 NULL。 */
		p = srt.path[i];
		BBST_node* tf = (i > 0 ? srt.path[i - 1] : NULL);

		if (p->bf == ET)
		{	/* p 原本是平衡的 */
			if (flag_shorter == LS)
				/* 左子树缩短，则右子树更高 */
				p->bf = RT;
			else
				p->bf = LT;
			flag_shorter = NS;
			rt = p;
		}
		else
		{	/* p 原本不平衡 */
			if (p->bf == LT && flag_shorter == LS || p->bf == RT && flag_shorter == RS)
			{	/* 较高的子树缩短了 */
				p->bf = ET;
				if (tf == NULL)
					/* p 已经是根了 */
					flag_shorter = UC;
				else if (tf->left == p)
					/* p 是 tf 的左子树 */
					flag_shorter = LS;
				else
					flag_shorter = RS;
				rt = p;
			}
			else
			{	/* 最复杂的情况：较矮的子树又缩短了 */
				/* q 是 p 较高的子树，未缩短 */
				q = (flag_shorter == LS ? p->right : p->left);
				if (q->bf == ET)
				{	/* q 原本平衡，做一个单旋即可 */
					flag_shorter = NS;
					if (q == p->right)
					{
						rt = rotate_L(p);
						q->bf = LT;
					}
					else
					{
						rt = rotate_R(p);
						q->bf = RT;
					}
				}
				else
				{	/* q 原本不平衡 */
					/* 先设置缩短标志 */
					if (tf == NULL)
						/* p 已经是根了 */
						flag_shorter = UC;
					else if (tf->left == p)
						/* p 是 tf 的左子树 */
						flag_shorter = LS;
					else
						flag_shorter = RS;

					if (p->bf == LT)
					{	/* ！这里是不是可以直接调用 balance_L？ */
						if (q->bf == LT)
						{	/* p, q 原本的平衡因子相同 */
							rt = rotate_R(p);
							p->bf = q->bf = ET;
						}
						else
						{	/* 否则，要做双旋 */
							rt = rotate_LR(p);
							switch (rt->bf)
							{
							case LT:
								p->bf = RT;
								q->bf = ET;
								break;
							case ET:
								p->bf = q->bf = ET;
								break;
							case RT:
								p->bf = ET;
								q->bf = LT;
								break;
							}
							rt->bf = ET;
						}
					}
					else
					{	/* ！这里是不是可以直接调用 balance_R？ */
						if (q->bf == RT)
						{
							rt = rotate_L(p);
							p->bf = q->bf = ET;
						}
						else
						{
							rt = rotate_RL(p);
							switch (rt->bf)
							{
							case RT:
								p->bf = LT;
								q->bf = ET;
								break;
							case ET:
								p->bf = q->bf - ET;
								break;
							case LT:
								p->bf = ET;
								q->bf = RT;
								break;
							}
							rt->bf = ET;
						}
					}
				}
			}
		}
		/* 最后将 rt 挂在 tf 上 */
		if (tf != NULL)
		{
			if (tf->left == p)
				tf->left = rt;
			else
				tf->right = rt;
		}
		else
			/* 根结点发生了变化 */
			return rt;
		--i;
	}
	return R;
}

/* 根据结点数，获取平衡二叉树的最大深度 */
unsigned int BBST_get_max_depth()
{
	/* 可用数学方法进行优化，暂时取一个固定值。 */
	return 15U;
}
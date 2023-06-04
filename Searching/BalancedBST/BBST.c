#include <stdlib.h>
#include "BBST.h"

/* ���������ߡ���־������ BBST_insert ����ʹ�ã� */
static bool_t flag_taller;

/* ���������̡���־������ BBST_delete ����ʹ�ã� */
static enum { LS = 1, RS = 0, NS = -1, UC = 2 } flag_shorter;
/* LS, RS �ֱ��ʾ�����������̣�
* NS��UC �ֱ��ʾû�����̺������˵�������˭����Ҫ��*/

/* ͳ�����н������� */
unsigned int BBST_ymr;

/* ������ D ������ R Ϊ�������У�
* ���� flag_taller ����������ָ���µĸ���ָ�롣 
* ������������ߡ��ˣ��� flag_taller �ᱻ��Ϊ True������Ϊ False��
* ������½����ʧ�ܣ���᷵�ؿ�ָ�� NULL�� */
BBST_node* BBST_insert(BBST_node* const R, const data_t D)
{
	BBST_node* p = NULL;	/* ָ���µĸ� */

	if (R == NULL)
	{
		p = (BBST_node*)malloc(sizeof(BBST_node));
		if (p == NULL)
			return NULL;	/* �½����ʧ�� */
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
		{	/* ���� D �Ѿ����� */
			flag_taller = False;
			p = R;
		}
		else if (crt < 0)
		{	/* �� D ���� R �������� */
			if ((R->left = BBST_insert(R->left, D)) == NULL)
				p = NULL;
			else
				if (flag_taller == True)
				{	/* �����������ߡ��� */
					switch (R->bf)
					{	/* ��� R ��ԭ���ģ�ƽ������ */
					case LT:
						/* ԭ���������ߣ�������ƽ�� */
						p = balance_L(R);
						flag_taller = False;
						break;
					case ET:
						/* ԭ���������ȸߣ�����ʹ���������� */
						R->bf = LT;
						flag_taller = True;
						p = R;
						break;
					case RT:
						/* ԭ���������ߣ�����ʹ�������ȸ� */
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
		{	/* �� D ���� R ���������� */
			if ((R->right = BBST_insert(R->right, D)) == NULL)
				p = NULL;
			else
				if (flag_taller == True)
				{	/* �����������ߡ��� */
					switch (R->bf)
					{	/* ��� R ��ԭ���ģ�ƽ������ */
					case RT:
						/* ԭ���������ߣ�������ƽ�� */
						p = balance_R(R);
						flag_taller = False;
						break;
					case ET:
						/* ԭ���������ȸߣ�����ʹ���������� */
						R->bf = RT;
						flag_taller = True;
						p = R;
						break;
					case LT:
						/* ԭ���������ߣ�����ʹ�������ȸ� */
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

/* ���� T Ϊ���������������� D��
* ����ҵ�����ô���ص� tar ָ��Ŀ���㣬par ָ���丸ĸ��
* ����par ָ������ʧ��ǰ���ʵ����һ����㣬tar Ϊ NULL��
* ע�⣺���Ŀ����ǡ���Ǹ�����ô par Ϊ NULL��
* ���⣬path ָ��Ӹ���Ŀ�����·������ NULL ������
* ������ʧ�ܣ����ǴӸ��� par ��·����*/
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

/* ���� R Ϊ��������ɾ������ D ���ڵĽ�㣬
* ����ָ���µĸ���ָ�롣*/
BBST_node* BBST_delete(BBST_node* const R, const data_t D)
{
	BBST_srt_t srt;
	int i;
	BBST_node* p, * q;
	/* rt ���ڽ��շ���ֵ�� */
	BBST_node* rt;

	srt = BBST_search(R, D);
	if (srt.tar == NULL)
	{	/* δ�ҵ�Ŀ���� */
		flag_shorter = NS;
		return R;
	}
	for (i = 0; srt.path[i] != NULL; ++i)
		;

	if (srt.tar->left != NULL && srt.tar->right != NULL)
	{	/* ��Ŀ�������������ӣ�����Ѱ������ֱ��ǰ�� */
		BBST_node* temp = srt.tar->left;
		srt.path[i++] = temp;
		while (temp->right != NULL)
		{
			temp = temp->right;
			/* ����Ӹ���Ŀ�����·�� */
			srt.path[i++] = temp;
		}
		srt.path[i] = NULL;
		/* ��ֱ��ǰ�������ݴ���Ŀ���� */
		srt.tar->data = temp->data;
		/* tar ָ��ֱ��ǰ������ΪҪɾ���Ľ�� */
		srt.tar = temp;
	}
	/* ���ˣ�tar ������һ�����ӣ����� path ���ǴӸ�������·�� */
	if (srt.tar == R)
	{	/* Ҫɾ�����ڵ㣬��ֱ�ӷ��������� */
		BBST_node* temp;
		if (R->left != NULL)
			temp = R->left;
		else
			temp = R->right;
		free(R);
		return temp;
	}
	--i;
	p = srt.path[--i];	/* tar �ĸ�ĸ */

	/* �� tar Ψһ���������� p �� */
	if (p->left == srt.tar)
	{
		p->left = (srt.tar->left != NULL ? srt.tar->left : srt.tar->right);
		flag_shorter = LS;	/* �����������̱�־ */
	}
	else
	{
		p->right = (srt.tar->left != NULL ? srt.tar->left : srt.tar->right);
		flag_shorter = RS;
	}
	free(srt.tar);
	//rt = R;

	while (flag_shorter != NS && i >= 0)
	{	/* ���ˣ�flag_shorter ָʾ p ���ĸ����������� */
		/* tf ָ�� p �ĸ�ĸ�����û����Ϊ NULL�� */
		p = srt.path[i];
		BBST_node* tf = (i > 0 ? srt.path[i - 1] : NULL);

		if (p->bf == ET)
		{	/* p ԭ����ƽ��� */
			if (flag_shorter == LS)
				/* ���������̣������������� */
				p->bf = RT;
			else
				p->bf = LT;
			flag_shorter = NS;
			rt = p;
		}
		else
		{	/* p ԭ����ƽ�� */
			if (p->bf == LT && flag_shorter == LS || p->bf == RT && flag_shorter == RS)
			{	/* �ϸߵ����������� */
				p->bf = ET;
				if (tf == NULL)
					/* p �Ѿ��Ǹ��� */
					flag_shorter = UC;
				else if (tf->left == p)
					/* p �� tf �������� */
					flag_shorter = LS;
				else
					flag_shorter = RS;
				rt = p;
			}
			else
			{	/* ��ӵ�������ϰ��������������� */
				/* q �� p �ϸߵ�������δ���� */
				q = (flag_shorter == LS ? p->right : p->left);
				if (q->bf == ET)
				{	/* q ԭ��ƽ�⣬��һ���������� */
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
				{	/* q ԭ����ƽ�� */
					/* ���������̱�־ */
					if (tf == NULL)
						/* p �Ѿ��Ǹ��� */
						flag_shorter = UC;
					else if (tf->left == p)
						/* p �� tf �������� */
						flag_shorter = LS;
					else
						flag_shorter = RS;

					if (p->bf == LT)
					{	/* �������ǲ��ǿ���ֱ�ӵ��� balance_L�� */
						if (q->bf == LT)
						{	/* p, q ԭ����ƽ��������ͬ */
							rt = rotate_R(p);
							p->bf = q->bf = ET;
						}
						else
						{	/* ����Ҫ��˫�� */
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
					{	/* �������ǲ��ǿ���ֱ�ӵ��� balance_R�� */
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
		/* ��� rt ���� tf �� */
		if (tf != NULL)
		{
			if (tf->left == p)
				tf->left = rt;
			else
				tf->right = rt;
		}
		else
			/* ����㷢���˱仯 */
			return rt;
		--i;
	}
	return R;
}

/* ���ݽ��������ȡƽ��������������� */
unsigned int BBST_get_max_depth()
{
	/* ������ѧ���������Ż�����ʱȡһ���̶�ֵ�� */
	return 15U;
}
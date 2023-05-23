#include <stdlib.h>
#include "BBST.h"

/* ���������ߡ���־������ BBST_insert ����ʹ�ã� */
static bool_t flag_taller;

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
* ע�⣺���Ŀ����ǡ���Ǹ�����ô par Ϊ NULL��*/
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

/* ���ݽ��������ȡƽ��������������� */
unsigned int BBST_get_max_depth()
{
	/* ������ѧ���������Ż�����ʱȡһ���̶�ֵ�� */
	return 15U;
}
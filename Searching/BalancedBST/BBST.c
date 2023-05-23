#include <stdlib.h>
#include "BBST.h"

/* ���������ߡ���־������ BBST_insert ����ʹ�ã� */
static bool_t flag_taller;

/* ������ D ������ R Ϊ�������У�
* ���� flag_taller ����������ָ���µĸ���ָ�롣 
* ������������ߡ��ˣ��� flag_taller �ᱻ��Ϊ True������Ϊ False��
* ������½����ʧ�ܣ���᷵�ؿ�ָ�� NULL�� */
BBST_node* BBST_insert(BBST_node* const R, const data_t D)
{
	BBST_node* p;	/* ָ���µĸ� */

	if (R == NULL)
	{
		p = (BBST_node*)malloc(sizeof(BBST_node));
		if (p == NULL)
			return NULL;	/* �½����ʧ�� */
		p->data = D;
		p->left = p->right = NULL;
		p->bf = ET;
		flag_taller = True;
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
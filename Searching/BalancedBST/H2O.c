﻿#include "BBST.h"
#include <stdio.h>

void BBST_print(const BBST_node* const T, bool_t concave, const char* const Tab, const unsigned int Level);

int main()
{
	BBST_node* pt = NULL;
	data_t dt;
	char cmd[5];
	BBST_srt_t rtemp;

	while (scanf("%s%d", cmd, &dt) == 2)
	{
		puts("======================");
		switch (cmd[0])
		{
		case 'i':	/* 插入 */
			pt = BBST_insert(pt, dt);
			BBST_print(pt, True, "--", 0U);
			break;
		case 'd':	/* 删除 */
			pt = BBST_delete(pt, dt);
			BBST_print(pt, True, "--", 0U);
			break;
		case 's':	/* 搜索 */
			rtemp = BBST_search(pt, dt);
			while (rtemp.path != NULL && *(rtemp.path) != NULL)
				printf("%d ", (*(rtemp.path++))->data);
			putchar('\n');
		}
		puts("======================");
	}
	return 0;
}

/* 打印平衡二叉树。
* 当 concave 为 True 时，使用凹入表；否则按中序遍历来打印。
* Tab 为分隔符。
* 外部调用本函数时 Level 应取 0。*/
void BBST_print(const BBST_node* const T, bool_t concave, const char* const Tab, const unsigned int Level)
{
	unsigned int i;

	if (T == NULL)
		return;
	if (concave == True)
	{
		for (i = 0; i < Level; ++i)
			printf("%s", Tab);
		printf("%d\n", T->data);
		if (T->left == NULL && T->right != NULL)
		{
			for (i = 0; i <= Level; ++i)
				printf("%s", Tab);
			putchar('\n');
		}
		else
			BBST_print(T->left, True, Tab, Level + 1);
		BBST_print(T->right, True, Tab, Level + 1);
	}
	else
	{
		BBST_print(T->left, False, Tab, Level + 1);
		printf("%d%s\n", T->data, Tab);
		BBST_print(T->right, False, Tab, Level + 1);
		if (Level == 0U)
			putchar('\n');
	}
}
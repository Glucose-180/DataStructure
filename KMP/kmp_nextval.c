#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strindex(const char *s, const char *t);

int main(int argc, char *argv[])
{
	char s[100];

	if (argc <= 1)
		return 1;
	while (scanf("%s", s) != EOF)
		printf("%d\n", strindex(s, argv[1]));
	return 0;
}

/* search t in s */
int strindex(const char *s, const char *t)
{
	int i = 0, j = 0;
	int *nextval_data;
	int len_t = strlen(t);

	nextval_data = (int *)malloc(sizeof(int) * len_t);
	{	/* calc nextval(i) and store in nextval_data */
		int i, k = -1;
		char c;
		nextval_data[0] = -1;
		for (i = 1; i < len_t; ++i)
		{
			c = t[i - 1];
			while (k >= 0 && c != t[k])
				k = nextval_data[k];
			if (t[i] == t[++k])
				nextval_data[i] = nextval_data[k];
			else
				nextval_data[i] = k;
		}
	}

	while (s[i] != '\0' && j < len_t)
	{
		if (j < 0 || s[i] == t[j])
			++i, ++j;
		else
			j = nextval_data[j];
	}
	free(nextval_data);
	if (j > 0 && t[j] == '\0')
		return i - len_t;
	else
		return -1;	/* not found or t is empyt */
}

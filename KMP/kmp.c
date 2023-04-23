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
	int *next_data;
	int len_t = strlen(t);

	next_data = (int *)malloc(sizeof(int) * len_t);
	{	/* calc next(i) and store in next_data */
		int i, k;
		char c;
		next_data[0] = -1;
		for (i = 1; i < len_t; ++i)
		{
			k = i - 1;
			c = t[k];
			do {
				k = next_data[k];
				if (k < 0)
					break;
			} while (c != t[k]);
			next_data[i] = k + 1;
		}
	}

	while (s[i] != '\0' && j < len_t)
	{
		if (j < 0 || s[i] == t[j])
			++i, ++j;
		else
			j = next_data[j];
	}
	free(next_data);
	if (j != 0 && t[j] == '\0')
		return i - len_t;
	else
		return -1;	/* not found or t is empyt */
}

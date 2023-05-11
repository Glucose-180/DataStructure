#include "malloc_g.h"

extern int8_t allocbuf[SL];

int main()
{
	char cmd[10];
	uint32_t n;
	int8_t* p;

	malloc_init();
	printf("SL: %u, EU: %u\n", SL, EU);
	printf("====== Available table ======\n");
	print_avail_table();
	putchar('\n');

	while (scanf("%s%u", cmd, &n) >= 1)
	{
		switch (cmd[0])
		{
		case 'm':	/* malloc */
			p = malloc_g(n);
			if (p == NULL)
				printf("NULL\n");
			else
				printf("Alloc: %lld, Size: %u\n", p - allocbuf, ((header*)(p-sizeof(header)))->size);
			break;
		case 'f':	/* free */
			free_g(allocbuf + n);
			break;
		default:
			break;
		}
		printf("====== Available table ======\n");
		print_avail_table();
		putchar('\n');
	}
	return 0;
}

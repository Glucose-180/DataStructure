#include "buddysystem.h"

extern int8_t allocbuf[];

int main()
{
	char cmd[10];
	uint32_t n;
	int8_t* p;

	bs_init();
	printf("EM: %u\n", EM);
	printf("====== Available table ======\n");
	print_freelist();
	putchar('\n');

	while (scanf("%s%u", cmd, &n) >= 1)
	{
		switch (cmd[0])
		{
		case 'm':	/* malloc */
			p = bs_malloc(n);
			if (p == NULL)
				printf("NULL\n");
			else
				printf("Alloc: %lld, log2size: %u\n", p - allocbuf, ((header*)(p - sizeof(header)))->log2size);
			break;
		case 'f':	/* free */
			bs_free(allocbuf + n);
			break;
		default:
			break;
		}
		printf("====== Available table ======\n");
		print_freelist();
		putchar('\n');
	}
	return 0;
}

#include "buddysystem.h"

struct {
	uint32_t size;
	header* first;
} freelist[EM + 1];
/* size: 2^0 ~ 2^EM */

/* Memory space to be allocated */
int8_t allocbuf[1U << EM];

static inline header* buddy(header* const P);

void bs_init()
{
	unsigned int i;
	header* p = (header*)allocbuf;

	for (i = 0; i <= EM; ++i)
	{
		freelist[i].size = (1U << i);
		freelist[i].first = NULL;
	}
	p->log2size = EM;
	p->next = NULL;
	p->tag = FREE;
	freelist[EM].first = p;
}

void* bs_malloc(const uint32_t Size)
{
	uint32_t n, i, k;
	header* p, * q;

	n = Size + sizeof(header);
	for (k = 0; k <= EM; ++k)
	{
		if (freelist[k].size >= n && freelist[k].first != NULL)
			break;
	}
	if (k > EM)
		return NULL;
	p = freelist[k].first;
	/* delete p in freelist */
	freelist[k].first = p->next;
	p->tag = OCCUPIED;
	if (k == 0)	/* almost impossible */
		return (void*)p;
	/* insert remaining blocks */
	for (i = k - 1; i > 0 && freelist[i].size >= n; --i)
	{
		q = (header*)((int8_t*)p + (1U << i));
		q->log2size = i;
		q->next = NULL;
		q->tag = FREE;
		freelist[i].first = q;
	}
	p->log2size = i + 1;
	return (void*)(p + 1);
}

int bs_free(void* const P)
{
	header* p = (header*)P - 1, * q;
	
	p->tag = FREE;
	for (q = buddy(p); (int8_t*)q - allocbuf < sizeof(allocbuf) && q->tag == FREE && q->log2size == p->log2size; p = q, q = buddy(p))
	{
		{	/* delete q from freelist */
			header* p;
			if (freelist[q->log2size].first == q)
				freelist[q->log2size].first = q->next;
			else
			{
				for (p = freelist[q->log2size].first; p != NULL && p->next != q; p = p->next)
					;
				if (p == NULL)
					return 1;	/* error */
				p->next = q->next;
			}
		}
		/* merge p and its buddy q */
		if (p < q)
			q = p;
		q->log2size += 1U;
	}
	/* insert p in freelist */
	p->next = freelist[p->log2size].first;
	freelist[p->log2size].first = p;
	return 0;
}

/* return P's buddy */
static inline header* buddy(header* const P)
{
	uint32_t loc, k;

	loc = (int8_t*)P - allocbuf;
	k = P->log2size;
	if ((loc >> (k + 1)) << (k + 1) == loc)	/* loc MOD 2^(k+1) == 0 */
		return (header*)((uint8_t*)P + (1U << k));
	else
		return (header*)((uint8_t*)P - (1U << k));
}

void print_freelist()
{
	uint32_t i;
	header* p;

	for (i = 0; i <= EM; ++i)
	{
		printf("freelist[%u]: Size is %u\n", i, freelist[i].size);
		for (p = freelist[i].first; p != NULL; p = p->next)
		{
			printf("\tStart: %lld, log2size: %u, End: %lld, Tag: %d;\n", (int8_t*)p - allocbuf, p->log2size, (int8_t*)p - allocbuf + (ptrdiff_t)(1 << p->log2size) - 1, p->tag);
		}
	}
}

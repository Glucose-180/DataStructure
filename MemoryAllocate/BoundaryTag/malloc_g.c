#include "malloc_g.h"

/* Memory space to be allocated */
int8_t allocbuf[SL];

static header* pav;

/* point to the foot of the node p points */
static inline header* foot_loc(header* p)
{
	return (header*)((int8_t*)p + p->size - sizeof(header));
}

void malloc_init()
{
	header* p, *q;

	pav = (header*)allocbuf;
	p = pav;

	p->next = p;
	p->size = SL;
	p->tag = FREE;
	p->last = p;

	q = foot_loc(p);
	q->head = p;
	q->tag = FREE;
}

/* malloc: First fit */
void* malloc_g(const uint32_t Size)
{
	uint32_t n;
	header* h, *f;

	n = Size + 2U * sizeof(header);
	for (h = pav; h != NULL && h->size < n && h->next != pav; h = h->next)
		;
	if (h == NULL || h->size < n)
		return NULL;	/* Not found */
	f = foot_loc(h);
	pav = h->next;	/* Convention */
	if (h->size - n < EU)
	{	/* allocate the single block */
		if (h == pav)
			/* no free space left */
			pav = NULL;
		else
		{
			h->last->next = pav;
			pav->last = h->last;
		}
		h->tag = f->tag = OCCUPIED;
	}
	else
	{	/* allocate the last n bytes */
		f->tag = OCCUPIED;
		h->size -= n;
		f = foot_loc(h);
		f->tag = FREE;
		f->head = h;
		h = f + 1;
		h->size = n;
		h->tag = OCCUPIED;
	}
	/* return the true address(after the header) */
	return (void*)(h + 1);
}

void free_g(void* const P)
{
	header* h, *f;
	uint32_t n;
	header* lf, * rh, * lh;
	int lf_tag, rh_tag;

	h = (header*)P - 1;
	f = foot_loc(h);
	n = h->size;

	lf = h - 1;	/* foot of the left block */
	if ((int8_t*)h - allocbuf <= 0)
		lf_tag = 1;	/* left terminal, consider as left block is occupied */
	else
		lf_tag = lf->tag;

	rh = f + 1;	/* head of the right block */
	if ((int8_t*)rh - allocbuf >= SL)
		rh_tag = 1;
	else
		rh_tag = rh->tag;
	switch ((lf_tag << 1) + rh_tag)
	{
	case 3:	/* both L and F are occupied */
		h->tag = f->tag = FREE;
		f->head = h;
		if (pav == NULL)
			pav = h->next = h->last = h;
		else
		{	/* insert h */
			h->next = pav;
			h->last = pav->last;
			pav->last->next = h;
			pav->last = h;
			pav = h;
		}
		break;
	case 2:	/* L is occupied */
		/* merge R and h */
		h->size = rh->size + n;
		if (rh->next == rh)
		{	/* only 1 block */
			h->next = h;
			h->last = h;
		}
		else
		{
			h->next = rh->next;
			h->last = rh->last;
		}
		f = foot_loc(h);
		f->head = h;
		h->tag = f->tag = FREE;
		h->last->next = h;
		h->next->last = h;
		pav = h;	/* it is necessary */
		break;
	case 1:	/* R is occupied */
		/* merge L and h */
		lh = lf->head;
		lh->size += n;
		f = foot_loc(h);
		f->head = lh;
		f->tag = FREE;
		break;
	default:/* both L and F are free */
		/* merge L and h */
		lh = lf->head;
		lh->size += n + rh->size;
		lf = foot_loc(lh);
		lf->head = lh;
		/* delete node R */
		rh->last->next = rh->next;
		rh->next->last = rh->last;
		pav = lh;	/* it is necessary */
		break;
	}
}

void print_avail_table()
{
	header* p;

	if (pav == NULL)
	{
		printf("NULL\n");
		return;
	}
	p = pav;
	do {
		printf("Start: %lld, Size: %u, End: %lld, Tag: %d;\n", (int8_t*)p - allocbuf, p->size, (int8_t*)p - allocbuf + (ptrdiff_t)p->size - 1, p->tag);
	} while ((p = p->next) != pav);
}

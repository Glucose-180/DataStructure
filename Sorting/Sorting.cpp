#include "Sorting.h"
#include <climits>

data_t buffer[N];

// Every sorting function returns count of swapping or moving

// Public swap function
// Always returns 1
static inline unsigned int swap_g(data_t* const D, const unsigned int I, const unsigned int J)
{
	data_t temp = D[I];
	D[I] = D[J];
	D[J] = temp;
	return 1U;
}

static unsigned int heapadjust(data_t* const H, const unsigned int T, const unsigned int N);

// Sort D[0] to D[N-1], from less to great
unsigned int bubblesort_g(data_t* const D, const unsigned int N)
{
	unsigned int i = N - 1, j;
	// last swap index
	unsigned int last;
	unsigned int ymr = 0U;

	if (N <= 0U)
		return ymr;

	// Data after i (not including i) has been sorted
	while (i > 0U)
	{
		last = 0U;
		for (j = 0U; j < i; ++j)
			if (dt_comp(D[j], D[j + 1]) > 0)
			{
				ymr += swap_g(D, j, j + 1);
				last = j;
			}
		i = last;
	}
	return ymr;
}

// Sort D[L] to D[R], from less to great
unsigned int qsort_g(data_t* const D, const unsigned int L, const unsigned int R)
{
	unsigned int i, last;
	unsigned int ymr = 0U;

	if (L >= R)
		return ymr;
	ymr += swap_g(D, L, (L + R) / 2U);
	last = L;
	for (i = L + 1U; i <= R; ++i)
		if (dt_comp(D[i], D[L]) < 0)
			ymr += swap_g(D, i, ++last);
	ymr += swap_g(D, last, L);
	if (last > 0U)
		ymr += qsort_g(D, L, last - 1U);
	ymr += qsort_g(D, last + 1U, R);
	return ymr;
}

// Only for heapsort
// Adjust a heap H with N data, whose top is T
static unsigned int heapadjust(data_t* const H, const unsigned int T, const unsigned int N)
{
	data_t temp;
	unsigned int t = T, i;
	unsigned int ymr = 0U;

	temp = H[T];
	for (i = 2U * t + 1U; i < N; ++i)
	{	// Start from the left child of H[T]
		// Search from top to bottom
		if (i + 1U < N && dt_comp(H[i], H[i + 1U]) < 0)
			++i;	// select the greater child
		if (dt_comp(temp, H[i]) >= 0)
			// The inserting location of H[T] has been found
			break;
		H[t] = H[i], ++ymr;
		t = i;
	}
	H[t] = temp, ++ymr;
	return ymr;
}

// Sort H[0] to H[N-1], from less to great
unsigned int heapsort_g(data_t* const H, const unsigned int N)
{
	unsigned int i = N / 2U;
	unsigned ymr = 0U;

	while (i-- > 0U)
		ymr += heapadjust(H, i, N);
	for (i = N; i-- > 0U; )
	{	// Data after i has been sorted
		// now move H[0] to the end
		ymr += swap_g(H, 0U, i);
		ymr += heapadjust(H, 0U, i);
		// now data including H[i] has been sorted
	}
	return ymr;
}

// Sort D[L] to D[R], from less to great
unsigned int mergesort_g(data_t* const D, data_t* const Buf, const unsigned int L, const unsigned int R)
{
	unsigned int ymr = 0U;
	unsigned int m = (L + R) / 2U, i, j, k;

	if (L >= R)
		return ymr;

	// recursion
	ymr += mergesort_g(D, Buf, L, m);
	ymr += mergesort_g(D, Buf, m + 1, R);

	// merging
	for (i = k = L, j = m + 1; i <= m && j <= R; ++k)
	{
		++ymr;
		if (dt_comp(D[i], D[j]) < 0)
			Buf[k] = D[i++];
		else
			Buf[k] = D[j++];
	}
	while (i <= m)
		Buf[k++] = D[i++], ++ymr;
	while (j <= R)
		Buf[k++] = D[j++], ++ymr;

	// copying
	for (k = L; k <= R; ++k)
		D[k] = Buf[k];
	return ymr;
}

// Sort H[0] to H[N-1], from less to great
unsigned int insertionsort_list(data_t* const D, const unsigned int N)
{
	unsigned int ymr = 0U;
	unsigned int* next = new unsigned int[N];
	unsigned int head = 0U,	// point to the first data in D
		i, j, k;

	// First: insert
	next[head] = UINT_MAX;	// initialize
	for (i = 1U; i < N; ++i)
	{	// insert D[i]
		if (dt_comp(D[i], D[head]) < 0)
			// set it as head
			next[i] = head, head = i;
		else
		{
			for (j = head, k = next[j];
				k < UINT_MAX && dt_comp(D[k], D[i]) < 0; j = k, k = next[k])
				;
			next[j] = i, next[i] = k;
		}
	}

	// Then: rearrange
	j = head;
	for (i = 0U; i < N; ++i)
	{
		// find the data that should be set at D[i]
		while (j < i)
			j = next[j];
		// k points to the next data to be arranged
		k = next[j];
		if (j != i)
		{
			unsigned int itemp;
			// swap D[j] and D[i]
			ymr += swap_g(D, i, j);
			itemp = next[j], next[j] = next[i], next[i] = itemp;
			// point to the data just moved
			next[i] = j;
		}
		j = k;
	}
	delete[] next;
	return ymr;
}

// Sort D[L] to D[R], from less to great
// quick sort without recursion
unsigned int qsort_ng(data_t* const D, const unsigned int L, const unsigned int R)
{
	typedef struct stack_t {
		unsigned int l, r;
	} stack_t;

	stack_t* stack;

	unsigned int ymr = 0U,
		sp = 0U;	// stack pointer

	if (R <= L)
		return ymr;
	stack = new stack_t[R - L + 1];
	// push
	stack[sp].l = L, stack[sp].r = R, ++sp;

	while (sp > 0U)
	{
		unsigned int l, r, i, last;
		// pop
		l = stack[--sp].l, r = stack[sp].r;
		if (r <= l)
			continue;
		if (r == l + 1)
		{
			if (dt_comp(D[l], D[r]) > 0)
				ymr += swap_g(D, l, r);
			continue;
		}
		// r - l >= 2U
		ymr += swap_g(D, l, (l + r) / 2U);
		last = l;
		for (i = l + 1U; i <= r; ++i)
			if (dt_comp(D[i], D[l]) < 0)
				ymr += swap_g(D, i, ++last);
		ymr += swap_g(D, last, l);
		// push
		if (last > 0U)
			stack[sp].l = l, stack[sp].r = last - 1U, ++sp;
		stack[sp].l = last + 1U, stack[sp].r = r, ++sp;
	}
	delete[] stack;
	return ymr;
}

// Sort D[0] to D[N-1], from less to greater
// using linked list
unsigned int selectionsort_list(data_t* const D, const unsigned int N)
{
	typedef struct list_node {
		data_t data;
		list_node* next;
	} lnode;
	lnode* head, * p, * q, * temp;
	unsigned int ymr = 0U, i;

	if (N <= 0U)
		return ymr;
	// head node: it doesnot contain valid data
	head = new lnode;
	head->next = NULL;
	for (i = 0U; i < N; ++i)
	{	// generate a new node
		temp = new lnode;
		temp->data = D[i];
		temp->next = head->next;
		head->next = temp;
	}
	// begin sorting
	for (p = head; p->next != NULL; p = p->next)
	{	//select a node and hang it after p
		temp = p;
		for (q = p; q->next != NULL; q = q->next)
		{	// let temp points to the prior of the minimum node after p
			if (dt_comp(q->next->data, temp->next->data) < 0)
				temp = q;
		}
		q = temp, temp = temp->next;
		// now temp points to the minumum node
		if (p->next != temp)
		{	// hang temp after p
			q->next = temp->next;
			temp->next = p->next;
			p->next = temp;
			++ymr;
		}
	}
	// write back
	p = head->next;
	delete head;
	for (i = 0U; p != NULL; p = q, ++i)
	{
		q = p->next;
		D[i] = p->data;
		delete p;
	}
	return ymr;
}

// Sort D[0] to D[N-1], from less to greater
// data_t should be unsigned int!
unsigned int radixsort(data_t* const D, const unsigned int N)
{
	const static unsigned int pow10[] = {
		1U,10U,100U,1000U,10000U,100000U,1000000U,
		10000000U,100000000U,1000000000U
	};
	typedef struct list_node {
		data_t data;
		list_node* next;
	} lnode;
	unsigned int ymr = 0U, i, radix, j = 0U;
	lnode* list_head[10], * p, * head, * q;

	if (N <= 0U)
		return ymr;
	for (i = 0U; i < 10U; ++i)
		list_head[i] = NULL;
	for (i = 0U; i < N; ++i)
	{	// Distribute first
		// NOTE: every time, we insert the data in the first,
		// so it may cause instability
		p = new lnode;
		p->data = D[i];
		radix = (p->data) % pow10[j + 1] / pow10[j];
		p->next = list_head[radix];
		list_head[radix] = p;

		++ymr;
	}

	while (true)
	{
		bool flag_unique = false;
		// Collect
		lnode* tail;
		// find the head of new list
		for (i = 0U; i < 10U && list_head[i] == NULL; ++i)
			;
		head = list_head[i];
		list_head[i] = NULL;
		for (tail = head; tail->next != NULL; tail = tail->next)
			;
		for (++i; i < 10U; ++i)
		{
			if (list_head[i] == NULL)
				continue;
			tail->next = list_head[i];
			list_head[i] = NULL;
			for (tail = head; tail->next != NULL; tail = tail->next)
				;

			++ymr;
		}

		++j;
		// Distribute again
		for (p = head; p != NULL; p = q)
		{
			radix = (p->data) % pow10[j + 1] / pow10[j];
			if (list_head[radix] == NULL)
				list_head[radix] = p;
			else
			{
				for (q = list_head[radix]; q->next != NULL; q = q->next)
					;
				q->next = p;
			}
			q = p->next, p->next = NULL;
			// q must keeps p->next temporarily

			++ymr;
		}

		// Check whether there is only one list
		for (i = 0U; i < 10U; ++i)
		{
			if (list_head[i] != NULL)
			{
				if (flag_unique == true)
					break;
				else
					flag_unique = true;
			}
		}
		if (i >= 10U)
			// only one list
			break;
	}

	for (i = 0U; i < 10U; ++i)
		if (list_head[i] != NULL)
			break;
	head = list_head[i];
	// write back
	p = head;
	for (i = 0U; p != NULL; p = q, ++i)
	{
		q = p->next;
		D[i] = p->data;
		delete p;
	}
	return ymr;
}

#include "Sorting.h"

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
	ymr += swap_g(D, L, (L + R) / 2);
	last = L;
	for (i = L + 1; i <= R; ++i)
		if (dt_comp(D[i], D[L]) < 0)
			ymr += swap_g(D, i, ++last);
	ymr += swap_g(D, last, L);
	if (last > 0)
		ymr += qsort_g(D, L, last - 1);
	ymr += qsort_g(D, last + 1, R);
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
	for (i = 2 * t + 1; i < N; ++i)
	{	// Start from the left child of H[T]
		// Search from top to bottom
		if (i + 1 < N && dt_comp(H[i], H[i + 1]) < 0)
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

unsigned int heapsort_g(data_t* const H, const unsigned int N)
{
	unsigned int i = N / 2;
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

unsigned int mergesort_g(data_t* const D, data_t* const Buf, const unsigned int L, const unsigned int R)
{
	unsigned int ymr = 0U;
	unsigned int m = (L + R) / 2, i, j, k;

	if (L >= R)
		return ymr;

	// recursion
	ymr += mergesort_g(D, Buf, L, m);
	ymr += mergesort_g(D, Buf, m + 1, R);

	// merging
	for (i = k = L, j = m + 1; i <= m && j <= R; ++k)
	{
		++ymr;
		if (D[i] < D[j])
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
#ifndef __SORTING_H__
#define __SORTING_H__

typedef int data_t;

unsigned int bubblesort_g(data_t* const D, const unsigned int N);
unsigned int qsort_g(data_t* const D, const unsigned int L, const unsigned int R);
unsigned int heapsort_g(data_t* const H, const unsigned int N);

static inline int dt_comp(const data_t X, const data_t Y)
{
	if (X < Y)
		return -1;
	else if (X == Y)
		return 0;
	else
		return 1;
}

#endif
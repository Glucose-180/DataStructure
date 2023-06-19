#ifndef __SORTING_H__
#define __SORTING_H__

typedef int data_t;

unsigned int bubblesort_g(data_t* const D, const unsigned int N);
unsigned int qsort_g(data_t* const D, const unsigned int L, const unsigned int R);
unsigned int heapsort_g(data_t* const H, const unsigned int N);
unsigned int mergesort_g(data_t* const D, data_t* const Buf, const unsigned int L, const unsigned int R);
unsigned int insertionsort_list(data_t* const D, const unsigned int N);
unsigned int qsort_ng(data_t* const D, const unsigned int L, const unsigned int R);
unsigned int selectionsort_list(data_t* const D, const unsigned int N);

// Size of buffer, also used for mergesort
const unsigned int N = 100;

extern data_t buffer[N];

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
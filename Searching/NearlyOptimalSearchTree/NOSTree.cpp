#include "NOSTree.h"

static treenode* _NOSTree(const data_t* const R, weight_t* const Sw, const int Low, const int High);
static inline weight_t wabs(const weight_t X);

/* Generate a Nearly optimal search tree from R[0] to R[N-1] with weight W[...] */
treenode* generate_NOST(const data_t* const R, weight_t* const W, const int N)
{
	weight_t* sw;
	int i;

	if (N <= 0)
		return NULL;
	sw = new weight_t[N + 1];
	*sw++ = 0;
	for (i = 0; i < N; ++i)
		sw[i] = sw[i - 1] + W[i];
	return _NOSTree(R, sw, 0, N - 1);
}

static treenode* _NOSTree(const data_t* const R, weight_t* const Sw, const int Low, const int High)
{
	int i, k = Low - 1;
	weight_t wmin;
	treenode* t;

	if (Low > High)
		return NULL;
	for (wmin = WINF, i = Low; i <= High; ++i)
	{
		weight_t temp;
		if ((temp = wabs(Sw[High] + Sw[Low - 1] - Sw[i] - Sw[i - 1])) < wmin)
			k = i, wmin = temp;
	}
	if (k < Low)
		return NULL;	/* Error */
	t = new treenode;
	t->data = R[k];
	t->left = _NOSTree(R, Sw, Low, k - 1);
	t->right = _NOSTree(R, Sw, k + 1, High);
	return t;
}

treenode* search(treenode* const T, const data_t K)
{
	treenode* p = T;

	while (p != NULL)
	{
		if (p->data == K)
			break;
		else if (p->data < K)
			p = p->right;
		else
			p = p->left;
	}
	return p;
}

static inline weight_t wabs(const weight_t X)
{
	if (X < (weight_t)0)
		return -X;
	else
		return X;
}
#include "NOSTree.h"

#ifndef NMAX
#define NMAX 20
#endif

using namespace std;

data_t tdata[NMAX];
weight_t tweight[NMAX];

int main()
{
	data_t dtemp, key;
	weight_t wtemp;
	treenode* tree, * p;
	int n = 0, i;
	char c;

	do {
		cin >> dtemp;
		tdata[n++] = dtemp;
		cin.get(c);
	} while (c == ' ');

	for (i = 0; i < n; ++i)
	{
		cin >> wtemp;
		tweight[i] = wtemp;
	}
	tree = generate_NOST(tdata, tweight, n);
	cin >> key;
	p = search(tree, key);
	if (p == NULL)
		cout << "NULL" << endl;
	else
		cout << p->data << endl;
	return 0;
}

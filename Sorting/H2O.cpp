#include <iostream>
#include "Sorting.h"

using namespace std;

const unsigned int N = 100;

data_t dt[N], buf[N];

int main()
{
	unsigned int n, i, ymr;

	for (n = 0U; n < N; ++n)
		if (!(cin >> dt[n]))
			break;
	
	// bubblesort
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = bubblesort_g(buf, n);
	cout << "After bubblesort:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;

	// qsort
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = (n > 0U ? qsort_g(buf, 0, n - 1) : 0U);
	cout << "After qsort:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;

	// heapsort
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = heapsort_g(buf, n);
	cout << "After heapsort:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;
	return 0;
}

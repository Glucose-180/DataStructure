#include <iostream>
#include "Sorting.h"

using namespace std;

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

	// mergesort
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = (n > 0U ? mergesort_g(buf, buffer, 0, n - 1) : 0U);
	cout << "After mergesort:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;

	// list
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = insertionsort_list(buf, n);
	cout << "After listinsertionsort:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;

	// qsort without recursion
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = (n > 0U ? qsort_ng(buf, 0U, n - 1U) : 0U);
	cout << "After qsort without recursion:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;

	// selectionsort using linked list
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = selectionsort_list(buf, n);
	cout << "After selectionsort using linked list:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;

	// radixsort
	for (i = 0U; i < n; ++i)
		buf[i] = dt[i];
	ymr = radixsort(buf, n);
	cout << "After radixsort:\n\t";
	for (i = 0U; i < n; ++i)
		cout << buf[i] << ' ';
	cout << "\n\tCounter: " << ymr << endl;
	return 0;
}

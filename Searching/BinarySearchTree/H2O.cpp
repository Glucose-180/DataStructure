#include "BST.h"

using namespace std;

int main()
{
	treenode* t = NULL, * rp, * rt;
	data_t dt, target;
	char c;

	do {
		cin >> dt;
		cin.get(c);
		t = BST_add_node(t, dt);
	} while (c != '\n');
	cout << "==============" << endl;
	BST_print(t, false, " ");
	cout << endl;
	BST_print(t, true);
	cout << "==============" << endl;
	while (cin >> target)
	{
		BST_search(t, target, rp, rt);
		if (rp == NULL)
			cout << "NULL";
		else
			cout << rp->data;
		cout << '\t';
		if (rt == NULL)
			cout << "NULL";
		else
			cout << rt->data;
		cout << endl;
	}
	return 0;
}
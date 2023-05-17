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
	BST_print(t, true, "--");
	cout << "==============" << endl;
	while (cin >> c >> target)
	{
		if (c == 's')
		{	// search
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
		else if (c == 'd')
		{	// delete
			t = BST_delete_node(t, target);
		}
		else if (c == 'a')
		{	// add
			t = BST_add_node(t, target);
		}
		if (c == 's')
			continue;
		cout << "==============" << endl;
		BST_print(t, false, " ");
		cout << endl;
		BST_print(t, true, "--");
		cout << "==============" << endl;
	}
	return 0;
}
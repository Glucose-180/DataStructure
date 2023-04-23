#include <vector>
#include <string>
#include <iostream>
#include <cstddef>
#include <climits>

using namespace std;

struct huf_tree_node {
	int weight;
	int parent;
	int left, right;
};

huf_tree_node* huf_tree;

struct char_t {
	char c;
	int w;
};

vector<char_t> weights_of_char;

huf_tree_node* huffman_coding(const vector<char_t>& weights_of_char);
string* getcode(const huf_tree_node* const T, const size_t N);

int main()
{
	char_t temp;
	string* code;
	size_t n, i;

	while (cin >> temp.c)
	{
		cin >> temp.w;
		weights_of_char.push_back(temp);
	}
	huf_tree = huffman_coding(weights_of_char);
	if (huf_tree == NULL)
		return 1;
	n = weights_of_char.size();
	code = getcode(huf_tree, n);
	for (i = 0; i < n; ++i)
		cout << weights_of_char.at(i).c << '\t' << code[i] << endl;
	return 0;
}

huf_tree_node* huffman_coding(const vector<char_t>& weights_of_char)
{
	huf_tree_node* huf_tree;
	size_t n, m, i, j;

	m = 2 * (n = weights_of_char.size()) - 1;
	if (n < 2)
		return NULL;
	huf_tree = new huf_tree_node[m];
	if (huf_tree == NULL)
		return NULL;
	// initialize
	for (i = 0; i < n; ++i)
	{
		huf_tree[i].weight = weights_of_char.at(i).w;
		huf_tree[i].parent = -1;
		huf_tree[i].left = huf_tree[i].right = -1;
	}
	for (; i < m; ++i)
	{
		huf_tree[i].weight = 0;
		huf_tree[i].parent = -1;
		huf_tree[i].left = huf_tree[i].right = -1;
	}

	for (i = n; i < m; ++i)
	{
		size_t s1, s2;	// index of two nodes whose weights are least
		int wl1, wl2;	// wieghts
		s1 = 0;
		s2 = 1;
		wl1 = wl2 = INT_MAX;
		for (j = 0; j < i; ++j)
		{
			if (huf_tree[j].parent >= 0)
				continue;
			if (huf_tree[j].weight <= wl1)
			{
				wl2 = wl1;
				wl1 = huf_tree[j].weight;
				s2 = s1;
				s1 = j;
			}
			else if (huf_tree[j].weight <= wl2)
			{
				wl2 = huf_tree[j].weight;
				s2 = j;
			}
		}
		huf_tree[s1].parent = i;
		huf_tree[s2].parent = i;
		huf_tree[i].left = s1;
		huf_tree[i].right = s2;
		huf_tree[i].weight = huf_tree[s1].weight + huf_tree[s2].weight;
	}
	return huf_tree;
}

string* getcode(const huf_tree_node* const T, const size_t N)
{
	string* code;
	size_t i;
	int c, f;

	code = new string[N];
	for (i = 0; i < N; ++i)
	{
		code[i] = "";
		for (c = i, f = T[i].parent; f >= 0; c = f, f = T[f].parent)
		{
			if (c == T[f].left)
				code[i] = '0' + code[i];
			else
				code[i] = '1' + code[i];
		}
	}
	return code;
}
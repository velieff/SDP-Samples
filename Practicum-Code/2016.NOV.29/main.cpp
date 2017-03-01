#include <list>
#include <queue>
#include <iostream>
#include "tree.cpp"

using std::cout;
using std::queue;
using std::list;

bool is_leaf(Tree t) // checks if the tree is leaf
{
	return t.getSubtrees().empty();
}

int sum_leaves(Tree t, int& sum) // returns the sum of all leaves of the tree
{
	if (is_leaf(t))
		sum += t.getRoot();
	else
	{
		for (list<Tree>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); it++)
			sum_leaves(*it, sum);
	}
	return sum;
}

void DFS(const Tree& t)
{
	cout << t.getRoot() << ' '; 
	for (list<Tree>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); ++it)
		DFS(*it);
}

void BFS(Tree const& tree)
{
	queue<Tree> q;
	q.push(tree);

	while (!q.empty())
	{
		Tree const& t = q.front();
		cout << t.getRoot() << ' ';
		for (list<Tree>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); it++)
			q.push(*it);
		q.pop();
	}
}

int depth(Tree const& t, int& curr_len, int& max_len) // finds the longest rout in the tree and returns length of the rout as depth
{
	if (is_leaf(t))
	{
		if (curr_len > max_len)
			max_len = curr_len;
	}

	curr_len++;
	for (list<Tree>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); ++it)
		depth(*it, curr_len, max_len);
	curr_len--;
	return max_len;
}

int breadth(Tree const& t, int& max_b) // finds the root with the biggest number of children and returns the number as breadth
{
	int i = 0;
	for (list<Tree>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); ++it, i++)
		breadth(*it, max_b);

	if (i > max_b)
		max_b = i;

	return max_b;
}

int main()
{
	// (1 (2 (3) (4)) (5 (6) (7) (8)) (9))
	Tree tree(1);
	tree.addChild(Tree(2).addChild(Tree(3)).addChild(Tree(4)))
		.addChild(Tree(5).addChild(Tree(6)).addChild(Tree(7)).addChild(Tree(8)))
		.addChild(Tree(9));
	// cout << tree;

	Tree t(42);
	cout << "is leaf: "<< is_leaf(t) << '\n';

	int sum = 0;
	cout << "sum of leaves: " << sum_leaves(tree, sum) << '\n';

	cout << "DFS: "; DFS(tree); cout << '\n';

	cout << "BFS: "; BFS(tree); cout << '\n';

	int curr_len = 1, max_len = 1;
	cout << "depth of tree: " << depth(tree, curr_len, max_len) << '\n';

	int max_b = 0;
	cout << "breadth of tree: " << breadth(tree, max_b) << '\n';

	return 0;
}
#include <list>
#include <iostream>
#include "tree.cpp"
#include"BinaryTree.h"
#include<queue>

using std::list;

/*
Да се дефинира функция prefixOfLevel, която получава като параметри
двоично дърво t и опашка от числа q, която проверява дали опашката
от числа q е префикс на списъка от числа на някое ниво в дървото t,
четени от ляво на дясно. Ако такова ниво съществува, функцията да
връща номера му, в противен случай да връща -1.
При няколко възможни отговора да се върне произволен от тях.
*/

int prefixOfLevel(Tree t, queue<int> q)
{
	queue<Tree> qq;
	list<list<int>> ll;
	qq.push(t);
	qq.push(Tree());
	int level = 0;

	while (!q.empty())
	{
		Tree const& t = qq.front();
		
		if (t.getRoot() == 0)
		{
			qq.pop();
			level++;
			qq.push(Tree());
		}

		for (list<Tree>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); it++)
			qq.push(*it);
	
		q.pop();
	}
	return level;
}

int main()
{
	return 0;
}
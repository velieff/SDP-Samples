#include <list>
#include <iostream>
#include "tree.cpp"
#include"BinaryTree.h"
#include<queue>

using std::list;

/*
�� �� �������� ������� prefixOfLevel, ����� �������� ���� ���������
������� ����� t � ������ �� ����� q, ����� ��������� ���� ��������
�� ����� q � ������� �� ������� �� ����� �� ����� ���� � ������� t,
������ �� ���� �� �����. ��� ������ ���� ����������, ��������� ��
����� ������ ��, � �������� ������ �� ����� -1.
��� ������� �������� �������� �� �� ����� ���������� �� ���.
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
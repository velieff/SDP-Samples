#include <list>
#include <iostream>
using std::list;
using std::ostream;

class Tree {
private:
	int root;
	// ������ �� ������ (������������ �� ������)
	list<Tree> subtrees;

public:
	// ��� �������������� �� ����� �������� ���� ������
	// �� �������� �� ���� ���������� addChild
	Tree(int _root = 0) : root(_root) {}

	// ������ �������� child ��� ������� � ������������ subtrees
	// ����� ���������� ��� �������,
	// �� �� ����� �� ������ addChild ������� ���� �� ������o, �.� ����:
	// tree.addChild(1).addChild(2).addChild(3);
	Tree& addChild(Tree const& child)
	{
		subtrees.push_back(child);
		return *this;
	}

	// ����� ���������� �� ������
	int getRoot() const { return root; }

	// ����� ���������� ��� ������� �� ����������
	list<Tree> const& getSubtrees() const { return subtrees; }

	// ������� �������
	friend ostream& operator<<(ostream& os, Tree const& tree)
	{
		os << '(' << tree.getRoot();
		for (list<Tree>::const_iterator it = tree.getSubtrees().begin(); it != tree.getSubtrees().end(); it++)
		{
			os << ' ' << *it;
		}
		return os << ')';
	}
};
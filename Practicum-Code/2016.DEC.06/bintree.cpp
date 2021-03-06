#include <iostream>
using namespace std;

//������� �� ������� ������ ����� ��������� �����
template <typename T>
struct TreeNode {
	//��������� �����
	T data;
	//�������� ��� ��� � ����� �����
	TreeNode *left, *right;

	TreeNode(T const& _data = T(),
		TreeNode* _left = NULL,
		TreeNode* _right = NULL)
		: data(_data), left(_left), right(_right) {}
};

//���� ���������� �� ��������� �� ���������� ��������� 
//����� ����� �� ��� �� �����������
template <typename T>
class BinaryTree;

//����������� ������� � ����� ���� ����� ��������
//���� ������ �� ����� ����� ����������� �� ����������
template <typename T>
class BinaryTreePosition {
private:
	//������������ �������� ��� �������� ��� �����
	TreeNode<T>** p;
public:
	BinaryTreePosition(TreeNode<T>*& rp) : p(&rp) {}

	//���� �������� ��������� �������������� ��
	//������� ��� ������ ��� ����
	operator bool() const {
		return *p != NULL;
	}

	//��������� ����������� �� ��������� ���� �������
	bool operator!() const {
		return *p == NULL;
	}

	//����� ���������� �� ������
	T& operator*() const {
		return (*p)->data;
	}

	//����� ����������� �� ����� ��� � ��������
	BinaryTreePosition operator+() const {
		if (*p == NULL)
			return *this;
		return BinaryTreePosition((*p)->right);
	}

	//����������� �� ���� ��� � ��������
	BinaryTreePosition operator-() const {
		if (*p == NULL)
			return *this;
		return BinaryTreePosition((*p)->left);
	}

	//��������� ������ �� BinaryTree<T> �� �������� �� ������� ����
	friend class BinaryTree<T>;

};

//��������� ����� ����������� ������� �� ������� ������
template <typename T>
class BinaryTree {
private:
	//�������� ��� ������ �� �������
	TreeNode<T>* r;

	//��������� ��� � ����������� �� �����������
	//���� �� �� ������ ����� ���� �� ������ �����������
	TreeNode<T>* copyNode(TreeNode<T>* n) {
		if (n == NULL)
			return n;
		cout << "Copying tree" << endl;
		return new TreeNode<T>(n->data, copyNode(n->left),
			copyNode(n->right));
	}

	//��� ���� ����� ����� � ������� � new
	//������ ����� �� ������� ������������
	//� ���� ���� �������� �����
	void eraseNode(TreeNode<T>* n) {
		if (n != NULL) {
			eraseNode(n->left);
			eraseNode(n->right);
			delete n;
		}
	}

	BinaryTree(TreeNode<T>* p) : r(copyNode(p)) {}

	void assignFrom(TreeNode<T>*& to, TreeNode<T>*& from) {
		// ��������� �� ������� ��������, �� �� � �������
		TreeNode<T>* toDelete = to;
		// ����������� ������ ��������
		to = from;
		// ���� � "����������", �.�. � �������, �� ����� �������
		// �������� ���������
		from = NULL;
		// ��������� ������� ��������, �� �� ������������ ��������
		// �� �����
		eraseNode(toDelete);
	}


public:

	using P = BinaryTreePosition<T>;

protected:
	//
	void assignFrom(P to, P from) {
		assignFrom(*to.p, *from.p);
	}

public:
	BinaryTree() : r(NULL) {}
	BinaryTree(T const& x, BinaryTree<T>&& lt = BinaryTree<T>(),
		BinaryTree<T>&& rt = BinaryTree<T>()) {
		r = new TreeNode<T>(x);
		assignFrom(r->left, lt.r);
		assignFrom(r->right, rt.r);
	}

	BinaryTree(BinaryTree const& bt) : r(copyNode(bt.r)) {
	}

	BinaryTree& operator=(BinaryTree const& bt) {
		if (this != &bt) {
			eraseNode(r);
			r = copyNode(bt.r);
		}
		return *this;
	}

	~BinaryTree() {
		eraseNode(r);
	}

	void assignFrom(P pos, BinaryTree<T>&& t) {
		assignFrom(pos, t.root());
	}

	void deleteAt(P pos) {
		TreeNode<T>* tmp = NULL;
		assignFrom(*pos.p, tmp);
	}

	P root() {
		return P(r);
	}


	BinaryTree leftTree() const {
		return BinaryTree(r->left);
	}

	BinaryTree rightTree() const {
		return BinaryTree(r->right);
	}

	bool empty() const {
		return r == NULL;
	}

};


template <typename T>
ostream& operator<<(ostream& os, BinaryTree<T> const& bt) {
	if (bt.empty())
		return os << '.';
	return os << '(' << *bt.root() << ' ' << bt.leftTree()
		<< ' ' << bt.rightTree() << ')';
}


template <typename T>
ostream& operator<<(ostream& os, BinaryTreePosition<T> pos) {
	if (!pos)
		return os << '.';
	return os << '(' << *pos << ' ' << -pos
		<< ' ' << +pos << ')';
}
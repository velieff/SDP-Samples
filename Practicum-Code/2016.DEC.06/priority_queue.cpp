#include "bintree.cpp"

//����������� ������ ����������� ���� ������� �����
template <typename T>
class PriorityQueue : BinaryTree<T> {
private:
	using P = BinaryTreePosition<T>;

	//�������� ������� �� ����� ������ �����
	//���� ����� ���������� ����������
	void insertAndSiftUp(P pos, T const& x) {
		if (pos) {
			//�������� ����� �� ������� �������
			//��� ��� �������� �� ���������
			P newpos = (x % 2) ? -pos : +pos;
			//���������� ��������� �� ��������� �����
			insertAndSiftUp(newpos, x);
			//��������� ������� � ��-����� ��������� ������
			if (*newpos > *pos)
				swap(*newpos, *pos);
		}
		else {
			//���������� �� ������ ������ ������� ������ �������
			//�.�. ����� �������� �� ������� �� ����� �����
			BinaryTree<T>::assignFrom(pos, BinaryTree<T>(x));
		}
	}

	//������ ����� �� ������ ���� ������� ��������
	P findLeaf(P pos) const {
		//��� ���� ���������� ������� ���������
		if (!pos || (!- pos && !+ pos))
			return pos;
		//��� ���� ��� ������ �����
		if (!- pos)
			return findLeaf(+pos);
		if (!+ pos)
			return findLeaf(-pos);
		return findLeaf((*pos % 2) ? -pos : +pos);
	}

	//����� ��-�������� ����
	P maxChild(P pos) {
		if (!- pos)
			return +pos;
		if (!+ pos)
			return -pos;
		return *-pos > *+pos ? -pos : +pos;

	}

	//����� ������ � ���-�������� ����
	//���� �������� � ������ �� �����
	//������ �� ������ ��������� ��
	void siftDown(P pos) {
		if (pos) {
			P maxcpos = maxChild(pos);
			if (maxcpos && *pos < *maxcpos)
				swap(*maxcpos, *pos);
			siftDown(maxcpos);
		}
	}

public:
	//O(1)
	bool empty() const { return BinaryTree<T>::empty(); }

	//O(1)
	T head() { return *BinaryTree<T>::root(); }

	//O(n)
	void enqueue_prioritized(T const& x) {
		insertAndSiftUp(BinaryTree<T>::root(), x);
	}

	//O(n)
	T dequeue_highest() {
		P rpos = BinaryTree<T>::root();
		T result = head();
		P pos = findLeaf(rpos);
		swap(*pos, *rpos);
		BinaryTree<T>::deleteAt(pos);
		siftDown(rpos);
		return result;
	}

};
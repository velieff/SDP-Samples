#include <iostream>
using namespace std;

#include "list.h"

template <typename T>
struct LinkedListElement {
	T data;
	LinkedListElement* next;

	LinkedListElement(T _data = T(), LinkedListElement* _next = NULL)
		: data(_data), next(_next) {}
};

template <typename T>
class LinkedList;

template <typename T>
class LinkedListIterator : public Iterator<T, LinkedListIterator<T> > {
	LinkedListElement<T>* p;
public:

	LinkedListIterator(LinkedListElement<T>* _p) : p(_p) {}

	typedef Iterator<T, LinkedListIterator<T> > I;

	// ������ ���������� � ������������ �� ����������� ��������� ���������
	using I::operator++;
	using I::operator--;

	// ��������� ��������� ������ � ����� ������ �������
	// O(1)
	I& operator++() {
		if (p != NULL)
			p = p->next;
		return *this;
	}


	// ��������� ��������� ����� � ����� ������ �������
	I& operator--() {
		// �� ����� �� �� ������� �����!!!
		return *this;
	}

	// ������ �� �������
	// O(1)
	T& operator*() const {
		// ��������: ���������� ������ �� � �������!
		return p->data;
	}

	// �������� �� ���������
	// O(1)
	operator bool() const {
		return p != NULL;
	}

	bool operator==(I const& it) const {
		return p == ((LinkedListIterator<T> const&)it).p;
	}

	friend class LinkedList<T>;

};

template <typename T>
class LinkedList : public List<T, LinkedListIterator<T> > {
public:

	typedef LinkedListIterator<T> I;
	typedef LinkedListElement<T> E;

private:
	LinkedListElement<T> *front, *back;

	// O(n)
	I findPrev(I it) {
		I pit = begin();
		while (pit && pit.p->next != it.p)
			++pit;
		// ������� ��������:
		// 1. �������� � ������
		// 2. ������ ����� ������
		// 3. ���������� � ���������
		return pit;
	}

public:
	LinkedList() : front(NULL), back(NULL) {}

	LinkedList(LinkedList const& l) : front(NULL), back(NULL) {
		this->copy(l);
	}

	LinkedList& operator=(LinkedList& l) {
		if (this != &l) {
			this->clean();
			this->copy(l);
		}
		return l;
	}

	~LinkedList() {
		this->clean();
	}

	// �������� �� ��������
	// O(1)
	bool empty() const {
		return front == NULL;
	}

	// ��������� ����� �������
	// O(n)
	bool insertBefore(T const& x, I const& it) {
		// ������ ��� ����� �������, ���� � �������� �� � ������!
		if (front == it.p || empty()) {
			front = new E(x, front);
			if (back == NULL)
				back = front;
			return true;
		}
		I pit = findPrev(it);
		return insertAfter(x, pit);
	}

	// ��������� ���� �������
	// O(1)
	bool insertAfter(T const& x, I const& it) {
		if (empty()) {
			front = back = new E(x);
			return true;
		}
		// front != NULL =! back
		if (!it)
			return false;
		it.p->next = new E(x, it.p->next);
		if (back == it.p)
			back = back->next;
		return true;
	}

	// ���������� ����� �������
	// O(n)
	bool deleteBefore(T& x, I const& it) {
		I pit = findPrev(it);
		return deleteAt(x, pit);
	}

	// ���������� �� �������
	// O(n)
	bool deleteAt(T& x, I const& it) {
		if (!empty() && front == it.p) {
			x = front->data;
			E* toDelete = front;
			front = front->next;
			if (back == toDelete)
				back = NULL;
			delete toDelete;
		}
		// front != it.p
		// �� �� �������� �� ������� ������ �������
		I pit = findPrev(it);
		return deleteAfter(x, pit);
	}

	// ���������� ���� �������
	// O(1)
	bool deleteAfter(T& x, I const& it) {
		if (!it || it.p->next == NULL)
			return false;
		// it.p != NULL && it.p->next != NULL
		E* toDelete = it.p->next;
		it.p->next = toDelete->next;
		x = toDelete->data;
		if (back == toDelete)

			back = it.p;
		delete toDelete;
			return true;
	}

	// ������ �� ������� �� �������
	// O(1)
	T& elementAt(I const& it) {
		return *it;
	}

	// ����� ��������� "������ �� �������"
	I begin() const {
		return I(front);
	}

	// ����� ��������� "���� �� �������"
	I end() const {
		return I(back);
	}

	// O(1)
	void append(LinkedList<T>& l2) {
		if (empty())
			front = l2.front;
		else
			back->next = l2.front;
		back = l2.back;
		l2.front = l2.back = NULL;
	}


};
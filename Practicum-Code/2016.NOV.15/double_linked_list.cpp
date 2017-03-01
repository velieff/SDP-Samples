#include <iostream>
using namespace std;

#include "list.h"

template <typename T>
struct DoubleLinkedListElement {
	T data;
	DoubleLinkedListElement *next, *prev;

	DoubleLinkedListElement(T _data = T(),
		DoubleLinkedListElement* _next = NULL,
		DoubleLinkedListElement* _prev = NULL)
		: data(_data), next(_next), prev(_prev) {}
};

template <typename T>
class DoubleLinkedList;

template <typename T>
class DoubleLinkedListIterator :
	public Iterator<T, DoubleLinkedListIterator<T> > {
	DoubleLinkedListElement<T>* p;
public:

	DoubleLinkedListIterator(DoubleLinkedListElement<T>* _p = NULL)
		: p(_p) {}

	typedef Iterator<T, DoubleLinkedListIterator<T> > I;

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
		if (p != NULL)
			p = p->prev;
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
		return p == ((DoubleLinkedListIterator<T> const&)it).p;
	}

	friend class DoubleLinkedList<T>;

};

template <typename T>
class DoubleLinkedList : public List<T, DoubleLinkedListIterator<T> > {
public:

	typedef DoubleLinkedListIterator<T> I;
	typedef DoubleLinkedListElement<T> E;

private:
	DoubleLinkedListElement<T> *front, *back;

public:
	DoubleLinkedList() : front(NULL), back(NULL) {}

	DoubleLinkedList(DoubleLinkedList const& l) : front(NULL), back(NULL) {
		this->copy(l);
	}

	DoubleLinkedList& operator=(DoubleLinkedList const& l) {
		if (this != &l) {
			this->clean();
			this->copy(l);
		}
		return l;
	}

	~DoubleLinkedList() {
		this->clean();
	}

	// �������� �� ��������
	// O(1)
	bool empty() const {
		return front == NULL;
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

	// ��������� ����� �������
	// O(1)
	bool insertBefore(T const& x, I const& it) {
		if (empty()) {
			back = front = new E(x);
			return true;
		}
		// back != NULL =! front
		if (!it)
			return false;
		// !empty() && it

		E* p = new E(x, it.p, it.p->prev);
		p->next->prev = p;
		if (front == it.p)
			// �������� ����� ������ �������
			front = p;
		else
			// �� ��� ����� ������, ����� �������� ������ �� ���� ��� p
			p->prev->next = p;

		return true;
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
		// !empty() && it

		E* p = new E(x, it.p->next, it.p);
		p->prev->next = p;
		if (back == it.p)
			// �������� ���� ��������� �������
			back = p;
		else
			// �� ��� ���� ���������, ����� ���������� ������ �� ���� ��� p
			p->next->prev = p;

		return true;
	}

	// ���������� ����� �������
	bool deleteBefore(T& x, I const& it) {
		I pit = it;
		--pit;
		return deleteAt(x, pit);
	}

	// ���������� �� �������
	bool deleteAt(T& x, I const& it) {
		if (empty() || !it)
			return false;
		// !empty() && it

		if (front == it.p)
			// ��������� ������
			front = it.p->next;
		else
			// �� ��������� ������, ����� ����� ��������
			it.p->prev->next = it.p->next;

		if (back == it.p)
			// ��������� ���������
			back = it.p->prev;
		else
			// �� ��������� ���������, ����� ����� �������
			it.p->next->prev = it.p->prev;

		x = *it;
		delete it.p;
		return true;
	}

	// ���������� ���� �������
	bool deleteAfter(T& x, I const& it) {
		I nit = it;
		++nit;
		return deleteAt(x, nit);
	}

	// O(1)
	void append(DoubleLinkedList<T>& l2) {
		if (empty())
			front = l2.front;
		else {
			back->next = l2.front;
			l2.front->prev = back;
		}
		back = l2.back;
		l2.front = l2.back = NULL;
	}

};
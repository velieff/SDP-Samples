#ifndef LIST_H_
#define LIST_H_

#include <iostream>

using namespace std;

template <typename T, typename P>
class List {
protected:

	// O(n)
	void copy(List<T, P> const& l) {
		for (P it = l.begin(); it; ++it)
			insertEnd(*it);
	}

	// O(n)
	void clean() {
		T tmp;
		while (deleteEnd(tmp));
	}

public:
	// �������� �� ��������
	virtual bool empty() const = 0;

	// ��������� ����� �������
	virtual bool insertBefore(T const&, P const&) = 0;

	// ��������� ���� �������
	virtual bool insertAfter(T const&, P const&) = 0;

	// ���������� ����� �������
	virtual bool deleteBefore(T&, P const&) = 0;

	// ���������� �� �������
	virtual bool deleteAt(T&, P const&) = 0;

	// ���������� ���� �������
	virtual bool deleteAfter(T&, P const&) = 0;

	// ������ �� ������� �� �������
	virtual T& elementAt(P const&) = 0;

	// ����� ��������� "������ �� �������"
	virtual P begin() const = 0;

	// ����� ��������� "���� �� �������"
	virtual P end() const = 0;

	// O(1)
	bool insertBegin(T const& x) {
		return insertBefore(x, begin());
	}

	// O(1)
	bool insertEnd(T const& x) {
		return insertAfter(x, end());
	}

	// O(1)
	bool deleteBegin(T& x) {
		return deleteAt(x, begin());
	}

	// O(1)
	bool deleteEnd(T& x) {
		return deleteAt(x, end());
	}

	virtual ~List() {}
};

template <typename T, typename ConcreteIterator>
class Iterator {
public:
	// Iterator it = l.begin();
	// it++; --> ����� ������� ������� (rvalue)
	// ++it; --> ����� ������ ������� (lvalue)
	// x = *it;
	// *it = 5;
	// if (!it) --> ���������
	// if (it) --> �������

	// ��������� ��������� ������ � ����� ������� �������
	ConcreteIterator operator++(int) {
		ConcreteIterator copy = (ConcreteIterator&)*this;
		operator++();
		return copy;
	}

	// ��������� ��������� ������ � ����� ������ �������
	virtual Iterator& operator++() = 0;

	// ��������� ��������� ����� � ����� ������� �������
	ConcreteIterator operator--(int) {
		ConcreteIterator copy = (ConcreteIterator&)*this;
		operator--();
		return copy;
	}

	// ��������� ��������� ����� � ����� ������ �������
	virtual Iterator& operator--() = 0;

	// ������ �� �������
	virtual T& operator*() const = 0;

	// �������� �� ���������
	virtual operator bool() const = 0;

	// �������� �� �����������
	bool operator!() const {
		return !operator bool();
	}

	// ���������
	virtual bool operator==(Iterator const&) const = 0;

	bool operator!=(Iterator const& it) const {
		return !(*this == it);
	}

	virtual ~Iterator() {}
};

template<typename T, typename P>
ostream& operator<<(ostream& os, List<T, P> const& l) {
	for (P it = l.begin(); it; ++it)
		os << *it << ' ';
	return os << endl;
}

#endif /* LIST_H_ */
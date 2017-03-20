#include<iostream>

#ifndef _STACK_HEADER_
#define _STACK_HEADER_

const int MAX_SIZE = 100;
const int EMPTY_STACK = -1;
template <typename T>
class Stack
{
	T a[MAX_SIZE];
	int top_index;
public:
	Stack() : top_index(EMPTY_STACK) {}

	bool empty() const
	{
		return top_index == EMPTY_STACK;
	}

	bool full() const
	{
		return top_index == MAX_SIZE - 1;
	}

	int size() const
	{
		return top_index + 1;
	}

	T top() const
	{
		if (!empty())
			return a[top_index];
		return T();
	}
	void push(T const& t)
	{
		if (!full())
			a[++top_index] = t;
	}

	T pop()
	{
		if (empty())
			return T();
		T tmp = a[top_index];
		a[top_index--] = T();
		return tmp;
	}

	T& operator[] (int i)
	{
		return a[i];
	}

	T operator[] (int i) const
	{
		return a[i];
	}
};

#endif
#pragma once
#include<iostream>
#include"Stack.h"

template<typename T>
class QueueFromStacks
{
private:
	Stack<T> st_1;
	Stack<T> st_2;
public:
	void enqueue(T const& x)
	{
		if (st_2.empty())
			st_1.push(x);
	}

	T dequeue()
	{
		while (!(st_1.empty()))
			st_2.push(st_1.pop());
		T R = st_2.pop();
		while (!(st_2.empty()))
			st_1.push(st_2.pop());
		return R;
	}

	T head() const
	{
		while (!(st_1.empty()))
			st_2.push(st_1.pop());
		T R = st_2.top();
		while (!(st_2.empty()))
			st_1.push(st_2.pop());
		return R;
	}

	bool empty() const
	{
		return st_1.empty();
	}

	bool full() const
	{
		return st_1.full();
	}
};
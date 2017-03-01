/**
*
*	Stack Implementation
*	Created By Merhat Veliev
*	https://github.com/velieff/SDP-Samples/blob/master/Stack/Stack.h
*
*/

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

	T top() const
	{
		if (empty())
		{
			std::cout << "Empty stack\n";
			return T();
		}

		return a[top_index];
	}
	void push(T const& t)
	{
		if (full())
		{
			std::cout << "Full stack!\n";
		}
		else
			a[++top_index] = t;
	}

	T pop()
	{
		if (empty())
		{
			std::cout << "Empty stack!\n";
			return T();
		}
		return a[top_index--];
	}
};

#endif

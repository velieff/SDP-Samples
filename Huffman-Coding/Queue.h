#ifndef _QUEUE_HEADER_
#define _QUEUE_HEADER_

#include <iostream>

const int MAX = 100;

template <typename T>
class Queue
{
private:
	T a[MAX];
	int front, back;
public:
	Queue()
	{
		this->front = 0;
		this->back = -1;
	}

	bool full() const
	{
		return front == (back + 2) % MAX;
	}

	bool empty() const
	{
		return front == (back + 1) % MAX;
	}

	int size() const
	{
		return (empty() ? 0 : ((back + MAX - front) % MAX + 1));
	}

	void enqueue(T const& x)
	{
		if (full())
			std::cout << "Full queue!\n";
		else
			a[++back %= MAX] = x;
	}

	T dequeue()
	{
		if (empty())
		{
			std::cout << "Empty queue!\n";
			return T();
		}
		else
		{
			T x = head();
			++front %= MAX;
			return x;
		}

	}

	T head() const
	{
		if (empty())
		{
			std::cout << "Empty queue!\n";
			return T();
		}
		else
			return a[front];
	}
};

#endif
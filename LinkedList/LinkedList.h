/**
*
*	Linked List Implementation
*	Created By Merhat Veliev
*	https://github.com/velieff/SDP-Samples/LinkedList/LinkedList.h
*
*/

#include<iostream>

#ifndef _LINKEDLISTHEADER_
#define _LINKEDLISTHEADER_

template <typename T>
class LinkedList
{
private:
	class Box
	{
	public:
		T data;
		Box* next;
		Box(){ this->next = NULL; }
		Box(T Data){ this->data = Data; this->next = NULL; }
		Box(T Data, Box* Next){ this->data = Data; this->next = Next; }
	};

	Box *first;
	Box *last;
	int size;

public:
	LinkedList()
	{
		initialize();
	}

	~LinkedList()
	{
		destroy();
	}

	LinkedList(LinkedList& other)
	{
		initialize();
		copy(other);
	}

	LinkedList& operator=(LinkedList& other)
	{
		if (this != &other)
		{
			destroy();
			copy(other);
		}
		return *this;
	}

	void add_first(const T& x)
	{
		if (empty())
		{
			this->first = new Box(x);
			this->last = this->first;
		}
		else
		{
			Box* box = new Box(x, this->first);
			this->first = box;
		}
		this->size++;
	}

	void add(const T& x)
	{
		if (empty())
		{
			this->first = new Box(x);
			this->last = this->first;
		}
		else
		{
			this->last->next = new Box(x);
			this->last = this->last->next;
		}
		this->size++;
	}

	void remove_first()
	{
		Box* box = this->first;
		this->first = this->first->next;
		if (this->first == NULL)
			this->last = NULL;
		delete box;
		this->size--;
	}

	void remove(int i)
	{
		if (i == 0)
			remove_first();

		else if (i < this->size)
		{
			Box* prev = this->first;
			for (int j = 0; j < i - 1; j++)
				prev = prev->next;

			Box* del = prev->next;
			if (i == this->size - 1)
				this->last = prev;
			prev->next = del->next;

			delete del;
			this->size--;
		}
	}

	T& get_first() const
	{
		return this->first->data;
	}

	T& get_last() const
	{
		return this->last->data;
	}

	T& operator[] (int i)
	{
		Box* box = this->first;
		for (int j = 0; j < i; j++)
			box = box->next;
		return box->data;
	}

	T operator[] (int i) const
	{
		Box* box = this->first;
		for (int j = 0; j < i; j++)
			box = box->next;
		return box->data;
	}

	bool empty() const
	{
		return this->size == 0;
	}

	int get_size() const
	{
		return this->size;
	}

	void sort()
	{
		for (int i = 0; i < this->size; i++)
		{
			Box* box = this->first;
			while (box->next)
			{
				if (box->data > box->next->data)
				{
					T tmp = box->data;
					box->data = box->next->data;
					box->next->data = tmp;
				}
				box = box->next;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& output, const LinkedList& list)
	{
		Box* box = list.first;
		for (int i = 0; i < list.size; i++)
		{
			output << box->data << '\n';
			box = box->next;
		}
		return output;
	}

private:
	void copy(LinkedList& other)
	{
		if (other.empty())
			return;
		this->first = new Box(other.first->data);
		Box* c1 = other.first;
		Box* c2 = this->first;
		while (c1->next)
		{
			c1 = c1->next;
			c2->next = new Box(c1->data);
			c2 = c2->next;
		}
		this->last = c2;
		this->size = other.size;
	}

	void destroy()
	{
		Box* curr = this->first;
		Box* prev = this->first;
		while (curr)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
		}
		initialize();
	}

	void initialize()
	{
		this->first = NULL;
		this->last = NULL;
		this->size = 0;
	}

public:
	class Iterator
	{
	private:
		Box* box;

	public:
		Iterator(Iterator& other)
		{
			this->box = other.box;
		}

		Iterator(Box* b)
		{
			this->box = b;
		}

		const T& operator*() const
		{
			return this->box->data;
		}

		T& operator*()
		{
			return this->box->data;
		}

		const T* operator->() const
		{
			return this->box->*data;
		}

		T* operator->()
		{
			return this->box->*data;
		}

		Iterator& operator++()
		{
			this->box = this->box->next;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator tmp(*this);
			++(*this);
			return tmp;
		}

		bool operator==(const Iterator& other) const
		{
			return this->box == other.box;
		}

		bool operator!=(const Iterator& other) const
		{
			return !(other == *this);
		}

		bool operator<(const Iterator& other) const
		{
			return this->box->data < other.box->data;
		}

		bool operator>(const Iterator& other) const
		{
			return other.box->data < this->box->data;
		}
	};

	Iterator begin()
	{
		return Iterator(this->first);
	}

	Iterator end()
	{
		return Iterator(this->last->next);
	}
};

#endif
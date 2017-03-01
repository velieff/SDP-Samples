#include<iostream>
#ifndef STACK_CHAR_H_
#define STACK_CHAR_H_


int const MAX = 100;
int const EMPTY_STACK = -1;



class Stack_char {
private:
	char a[MAX];	// aeaiaioeoa ia noaea
	int topIndex;	// eiaaen ia iineaaiey aeaiaio


public:

	// nucaaaaia ia i?acai noae
	Stack_char()
	{ 
		topIndex = EMPTY_STACK;
	}

	// naeaeoi?e

	// i?iaa?ea aaee noae a i?acai
	bool empty() const 
	{
		return topIndex == EMPTY_STACK;
	}

	// iaie?aia ia aeaiaioa ia au?oa ia noaea
	char top() const
	{
		if (empty())
		{
			std::cout << "A?aoea: iieo ca iiaea?aaia a i?acai noae!\n";
			return 0;
		}

		return a[topIndex];
	}

	// iooaoi?e

	// aee??aaia ia aeaiaio
	void push(char const& x)
	{
		if (full()) {
			std::cout << "A?aoea: iieo ca aee??aaia a iueai noae!\n";
		}
		else
			a[++topIndex] = x;
	}


	// ecee??aaia ia aeaiaio
	void pop()
	{
		if (empty()) {
			std::cout << "A?aoea: iieo ca ecee??aaia io i?acai noae!\n";
			return;
		}
		topIndex--;
	}

	// i?iaa?ea aaee noae a iueai
	bool full() const
	{
		return topIndex == MAX - 1;
	}

};

#endif
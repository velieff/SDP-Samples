#include<iostream>
#ifndef STACK_NUM_H_
#define STACK_NUM_H_


int const MAX_ = 100;
int const EMPTY_STACK_ = -1;



class Stack_num {
private:
	int a[MAX_];	// aeaiaioeoa ia noaea
	int topIndex;	// eiaaen ia iineaaiey aeaiaio


public:

	// nucaaaaia ia i?acai noae
	Stack_num()
	{
		topIndex = EMPTY_STACK_;
	}

	// naeaeoi?e

	// i?iaa?ea aaee noae a i?acai
	bool empty() const
	{
		return topIndex == EMPTY_STACK_;
	}

	// iaie?aia ia aeaiaioa ia au?oa ia noaea
	int top() const
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
	void push(int const& x)
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
		return topIndex == MAX_ - 1;
	}

};

#endif
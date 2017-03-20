/**
*
*	Hanoi Towers
*	Created By Merhat Veliev
*
*/

#include<iostream>
#include"HanoiTowers.h"

int main()
{
	int n;
	do
	{
		std::cout << "Insert number of discs: ";
		std::cin >> n;
	} while (n < 1 || n > 10);

	HanoiTowers h(n);
	char from, dest;

	while (!h.solved())
	{
		std::cout << h;
		std::cout << "Move from: ";
		std::cin >> from;
		std::cout << "Move to: ";
		std::cin >> dest;
		std::cout << h.move(from, dest);
	}

	h.finish();

	return 0;
}
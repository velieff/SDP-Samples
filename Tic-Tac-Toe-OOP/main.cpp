/**
*
*	Tic Tac Toe
*	Created By Merhat Veliev
*
*/

#include<iostream>
#include"TicTacToe.h"

int main()
{
	TicTacToe t;
	int n;
	do
	{
		std::cout << t;
		do
		{
			std::cout << t.turn();
			std::cin >> n;
		}
		while (!t.put(n));
	}
	while (!t.win() && !t.draw());

	return 0;
}

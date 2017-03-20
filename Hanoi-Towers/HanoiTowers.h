#include<iostream>
#include"Disc.h"
#include"Stack.h"

#ifndef _HANOI_TOWERS_HEADER_
#define _HANOI_TOWERS_HEADER_

class HanoiTowers
{
private:
	Stack<Disc> A, B, C;
	int num_of_discs;
	int moves;
	
	bool move_help(Stack<Disc>& from, Stack<Disc>& dest)
	{
		if (!from.empty() && (dest.empty() || dest.top() > from.top()))
		{
			dest.push(from.pop());
			this->moves++;
			return true;
		}
		return false;
	}

	void auto_solve(Stack<Disc>& from, Stack<Disc>& dest, Stack<Disc>& help, int step)
	{
		if (step == 1)
			move_help(from, dest);
		else
		{
			auto_solve(from, help, dest, step - 1);
			std::cout << *this;
			move_help(from, dest);
			std::cout << *this;
			auto_solve(help, dest, from, step - 1);
		}
	}

public:
	HanoiTowers(int N)
	{
		this->moves = 0;
		this->num_of_discs = N;
		for (int i = num_of_discs; i > 0; i--)
			A.push(Disc(i));
	}

	~HanoiTowers(){}

	const char* move(char From, char Dest)
	{
		bool is_successful = false;
		if (From == 'A' || From == 'a' || From == '1')
		{
			if (Dest == 'B' || Dest == 'b' || Dest == '2')
				is_successful = move_help(A, B);
			else if (Dest == 'C' || Dest == 'c' || Dest == '3')
				is_successful = move_help(A, C);
		}

		else if (From == 'B' || From == 'b' || From == '2')
		{
			if (Dest == 'A' || Dest == 'a' || Dest == '1')
				is_successful = move_help(B, A);
			else if (Dest == 'C' || Dest == 'c' || Dest == '3')
				is_successful = move_help(B, C);
		}

		else if (From == 'C' || From == 'c' || From == '3')
		{
			if (Dest == 'B' || Dest == 'b' || Dest == '2')
				is_successful = move_help(C, B);
			else if (Dest == 'A' || Dest == 'a' || Dest == '1')
				is_successful = move_help(C, A);
		}

		else if ((From == 'X' || From == 'x') && (Dest == 'X' || Dest == 'x'))
		{
			std::cout << "Auto solve...\n";
			auto_solve(this->A, this->C, this->B, A.size());
			return "";
		}

		return (is_successful ? "Successfully moved!\n\n\n" : "Illegal move!\n\n\n");
	}

	friend std::ostream& operator<<(std::ostream& s, const HanoiTowers& h)
	{
		for (int i = h.num_of_discs - 1; i >= 0; i--)
			s << h.A[i] << h.B[i] << h.C[i] << '\n';
		s << "          A                    B                    C\nMoves: " << h.moves << '\n';
		return s;
	}
	
	void finish() 
	{
		int opt_sol = std::pow(2, num_of_discs) - 1;
		std::cout << *this << "You have successfully solved it!\n";
		if (this->moves > opt_sol)
			std::cout << "Optimal solution: " << opt_sol << " move" << (opt_sol > 1 ? "s\n" : "\n");
	}

	bool solved() const
	{
		return (A.empty() && B.empty());
	}
};

#endif

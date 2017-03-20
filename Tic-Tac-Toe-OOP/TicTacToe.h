#include<iostream>

const int TABLE_SIZE = 3;
const char EMPTY = ' ';

class TicTacToe
{
private:
	bool player_turn;
	char table[TABLE_SIZE][TABLE_SIZE];
public:
	TicTacToe()
	{
		player_turn = true;
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			for (int j = 0; j < TABLE_SIZE; j++)
				table[i][j] = EMPTY;
		}
	}

	~TicTacToe(){}

	bool put(int n)
	{
		if (n < 1 || n > 9)
		{
			std::cout << "The number must be between 1 and 9.\n";
			return false;
		}
		switch(n)
		{
		case 1: return put(0, 0);
		case 2: return put(0, 1);
		case 3: return put(0, 2);
		case 4: return put(1, 0);
		case 5: return put(1, 1);
		case 6: return put(1, 2);
		case 7: return put(2, 0);
		case 8: return put(2, 1);
		case 9: return put(2, 2);
		};
	}

	friend std::ostream& operator<<(std::ostream& s, const TicTacToe& t)
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			for (int j = 0; j < TABLE_SIZE; j++)
				s <<' '<< t.table[i][j] << (j != TABLE_SIZE - 1 ? " |" : "");
			s << (i != TABLE_SIZE - 1 ? "\n---|---|---\n" : "\n");
		}
		return s;
	}

	const char* turn()
	{
		return (player_turn ? "Player 1 is on turn: " : "Player 2 is on turn: ");
	}

	bool draw() const
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			for (int j = 0; j < TABLE_SIZE; j++)
			{
				if (table[i][j] == EMPTY)
					return false;
			}
		}

		std::cout << *this << "Game is draw!\n";
		return true;
	}

	bool win() const
	{
		if ((table[0][0] != EMPTY && table[0][0] == table[1][1] && table[1][1] == table[2][2]) ||
			(table[0][2] != EMPTY && table[0][2] == table[1][1] && table[1][1] == table[2][0]))
		{
			who_wins();
			return true;
		}
		
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if ((table[i][0] != EMPTY && table[i][0] == table[i][1] && table[i][1] == table[i][2]) ||
				(table[0][i] != EMPTY && table[0][i] == table[1][i] && table[1][i] == table[2][i]))
			{
				who_wins();
				return true;
			}
		}
		return false;
	}

	private:
		void who_wins() const
		{
			std::cout << *this << (player_turn ? "Player 2 wins!\n" : "Player 1 wins!\n");
		}

		bool put(int i, int j)
		{
			if (table[i][j] != EMPTY)
			{
				std::cout << "The cell is not empty.\n";
				return false;
			}

			if (player_turn)
				table[i][j] = 'X';
			else
				table[i][j] = 'O';
			player_turn = !player_turn;
			return true;
		}
};
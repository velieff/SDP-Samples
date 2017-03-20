#include<iostream>

#ifndef _DISC_HEADER_
#define _DISC_HEADER_

class Disc
{
private:
	int size;
	char* preview;
public:
	Disc()
	{
		*this = Disc(0);
	}
	Disc(int Size)
	{
		switch (Size)
		{
		case 0: preview = "          |          "; break;
		case 1: preview = "         _|_         "; break;
		case 2:	preview = "        __|__        "; break;
		case 3:	preview = "       ___|___       "; break;
		case 4: preview = "      ____|____      "; break;
		case 5:	preview = "     _____|_____     "; break;
		case 6:	preview = "    ______|______    "; break;
		case 7:	preview = "   _______|_______   "; break;
		case 8: preview = "  ________|________  "; break;
		case 9: preview = " _________|_________ "; break;
		case 10: preview = "__________|__________"; break;
		};
		this->size = Size;
	}

	Disc& operator=(const Disc& other)
	{
		if (this != &other)
		{
			this->size = other.size;
			this->preview = other.preview;
		}
		return *this;
	}

	~Disc(){}

	char* get_preview() const
	{
		return this->preview;
	}
	int get_size() const
	{
		return this->size;
	}

	bool operator<(const Disc& other) const
	{
		return this->size < other.size;
	}
	bool operator>(const Disc& other) const
	{
		return other < *this;
	}

	friend std::ostream& operator<<(std::ostream& s, const Disc& d)
	{
		return s << d.preview;
	}
};

#endif

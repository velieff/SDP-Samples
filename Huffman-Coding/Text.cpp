#include<iostream>
#include<fstream>
#include"Text.h"

// this class is something like 'string' but it does not store char* it stores Symbol*
// I use Symbol because I can allocate more memory than I need
// if I use char* I have to resize it every time when I add a new element

Text::Text()
{
	this->num = 0;
	this->capacity = 4;
	this->s = new Symbol[capacity];
}

Text::~Text()
{
	destroy();
}

Text::Text(const Text& other)
{
	copy(other);
}

Text& Text::operator=(const Text& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

Text::Text(std::fstream& S)
{
	S.read((char*)&this->num, sizeof(this->num));
	this->s = new Symbol[num + 1];
	for (int i = 0; i < this->num; i++)
		this->s[i] = Symbol(S);
}

Text::Text(char* t)
{
	this->num = 0;
	add(t);
}

void Text::add(const Symbol& sym)
{
	if (this->capacity == this->num)
		resize();
	this->s[num] = sym;
	this->num++;
}

void Text::add(const char sym)
{
	add(Symbol(sym));
}
void Text::add(char* str)
{
	for (int i = 0; str[i]; i++)
		add(Symbol(str[i]));
}

int Text::get_size() const
{
	return this->num;
}

std::ostream& operator<<(std::ostream& output, const Text& t)
{
	for (int i = 0; i < t.num; i++)
		output << t.s[i];
	return output;
}

Symbol& Text::operator[] (int i)
{
	return this->s[i];
}

Symbol Text::operator[] (int i) const
{
	return this->s[i];
}

bool Text::empty() const
{
	return this->num == 0;
}

void Text::serialize(std::ostream& S)
{
	S.write((const char*)&this->num, sizeof(this->num));
	for (int i = 0; i < this->num; i++)
		this->s[i].serialize(S);
}

Text& Text::operator+=(const Text& t)
{
	for (int i = 0; i < t.num; i++)
		add(t.s[i]);
	return *this;
}

Text Text::operator+(const Text& t) const
{
	Text tmp(*this);
	tmp += t;
	return tmp;
}

void Text::copy(const Text& other)
{
	this->num = other.num;
	this->capacity = other.capacity;
	this->s = new Symbol[capacity];
	for (int i = 0; i < num; i++)
	{
		this->s[i] = other.s[i];
	}
}

void Text::destroy()
{
	delete[] this->s;
}

void Text::resize()
{
	this->capacity *= 2;
	Symbol* other = new Symbol[capacity];
	for (int i = 0; i < this->num; i++)
		other[i] = this->s[i];
	delete[] this->s;
	this->s = other;
}
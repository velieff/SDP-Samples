#include<iostream>
#include<fstream>
#include"Code.h"

int LEN(char* t)
{
	int num = 0;
	while (t[num])
		num++;
	return num;
}

void CPY(char* a, char* b)
{
	int num = 0;
	while (b[num])
	{
		a[num] = b[num];
		num++;
	}
	a[num] = '\0';
}

Code::Code()
{
	initialize();
}

Code::~Code()
{
	destroy();
}

Code::Code(const Code& other)
{
	copy(other);
}

Code& Code::operator=(const Code& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

Code::Code(char S)
{
	initialize();
	set_symbol(S);
}

Code::Code(int F)
{
	initialize();
	set_frequency(F);
}

Code::Code(char S, int F, char* C)
{
	set_symbol(S);
	set_frequency(F);
	this->code = new char[LEN(C) + 1];
	CPY(this->code, C);
}

Code::Code(std::istream& S)
{
	S.read((char*)&this->symbol, sizeof(this->symbol));
	int N;
	S.read((char*)&N, sizeof(N));
	this->code = new char[N + 1];
	S.read(this->code, N + 1);
	this->frequency = 0;
}

void Code::set(char S, int F, char* C)
{
	set_symbol(S);
	set_frequency(F);
	set_code(C);
}

void Code::set_symbol(char S)
{
	this->symbol = S;
}

void Code::set_frequency(int F)
{
	this->frequency = F;
}

void Code::set_code(char* C)
{
	destroy();
	this->code = new char[LEN(C) + 1];
	CPY(this->code, C);
}

char Code::get_symbol() const
{
	return this->symbol;
}

int Code::get_frequency() const
{
	return this->frequency;
}

char* Code::get_code() const
{
	return this->code;
}

void Code::add_to_code(char* parent_code, char x)
{
	int N = LEN(parent_code);
	delete[] this->code;
	this->code = new char[N + 2];
	if (N > 0)
		CPY(this->code, parent_code);
	this->code[N] = x;
	this->code[N + 1] = '\0';
}

std::ostream& operator<<(std::ostream& s, const Code& c)
{
	return s << c.symbol << ' ' << c.frequency << ' ' << c.code;
}

bool Code::operator<(const Code& other) const
{
	return this->frequency < other.frequency;
}

bool Code::operator>(const Code& other) const
{
	return this->frequency > other.frequency;
}


bool Code::operator==(const Code& other) const
{
	if (this->frequency != other.frequency || this->symbol != other.symbol)
		return false;
	int N = LEN(this->code);
	if (N != LEN(other.code))
		return false;
	for (int i = 0; i < N; i++)
	{
		if (this->code[i] != other.code[i])
			return false;
	}
	return true;
}

Code::operator bool() const
{
	int N = LEN(this->code);
	if (N == 0)
		return false;
	for (int i = 0; i < N; i++)
	{
		if (this->code[i] != '0' && this->code[i] != '1')
			return false;
	}
	return true;
}

Code& Code::operator++()
{
	this->frequency++;
	return *this;
}

Code Code::operator+(const Code& c)
{
	return Code(this->frequency + c.frequency);
}

void Code::serialize(std::ostream& S)
{
	S.write((const char*)&this->symbol, sizeof(this->symbol));
	int N = LEN(this->code);
	S.write((const char*)&N, sizeof(N));
	S.write(this->code, N + 1);
}

void Code::initialize()
{
	this->symbol = char(1);
	this->frequency = 1;
	this->code = new char[1];
	code[0] = '\0';
}

void Code::copy(const Code& other)
{
	set_symbol(other.symbol);
	set_frequency(other.frequency);
	this->code = new char[LEN(other.code) + 1];
	CPY(this->code, other.code);
}

void Code::destroy()
{
	delete[] this->code;
}
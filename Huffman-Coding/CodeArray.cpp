#include<iostream>
#include<fstream>
#include"Code.h"
#include"CodeArray.h"


CodeArray::CodeArray()
{
	this->num = 0;
	this->capacity = 4;
	this->codes = new Code[capacity];
}

CodeArray::~CodeArray()
{
	destroy();
}

CodeArray::CodeArray(const CodeArray& other)
{
	copy(other);
}

CodeArray& CodeArray::operator=(const CodeArray& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

CodeArray::CodeArray(std::fstream& S)
{
	S.read((char*)&this->num, sizeof(this->num));
	this->codes = new Code[num + 1];
	for (int i = 0; i < this->num; i++)
		this->codes[i] = Code(S);
}

void CodeArray::add(const Code& new_code)
{
	if (this->capacity == this->num)
		resize();
	this->codes[num] = new_code;
	this->num++;
}

int CodeArray::find(char S) const
{
	for (int i = 0; i < num; i++)
	{
		if (codes[i].get_symbol() == S)
			return i;
	}
	return -1;
}

Code CodeArray::remove(int i)
{
	if (!(empty()))
	{
		Code x = this->codes[i];
		this->num--;
		for (int j = i; j < this->num; j++)
			this->codes[j] = this->codes[j + 1];
		return x;
	}
	else
		return Code();
}

void CodeArray::add_or_increase(char S)
{
	int i = find(S);
	if (i == -1)
		add(Code(S));
	else
		++this->codes[i];
}

Code& CodeArray::get_code(char S) const
{
	for (int i = 0; i < this->num; i++)
	{
		if (this->codes[i].get_symbol() == S)
			return this->codes[i];
	}
	return Code();
}

int CodeArray::get_size() const
{
	return this->num;
}

void CodeArray::set_code(char S, char* code)
{
	int i = find(S);
	if (i == -1)
		return;
	this->codes[i].set_code(code);
}

std::ostream& operator<<(std::ostream& output, const CodeArray& arr)
{
	for (int i = 0; i < arr.num; i++)
		output << i+1 << ": "<< arr.codes[i] << '\n';
	return output;
}

Code& CodeArray::operator[] (int i) const
{
	return this->codes[i];
}

void CodeArray::swap(int i, int j)
{
	Code temp(this->codes[i]);
	this->codes[i] = this->codes[j];
	this->codes[j] = temp;
}

void CodeArray::sort()
{
	for (int i = 0; i < num; i++)
	{
		for (int j = num - 1; j > i; j--)
		{
			if (codes[j-1] > codes[j])
				swap(j - 1, j);
		}
	}
}

bool CodeArray::empty() const
{
	return this->num == 0;
}

void CodeArray::serialize(std::ostream& S)
{
	S.write((const char*)&this->num, sizeof(this->num));
	for (int i = 0; i < this->num; i++)
		this->codes[i].serialize(S);
}

void CodeArray::copy(const CodeArray& other)
{
	this->num = other.num;
	this->capacity = other.capacity;
	this->codes = new Code[capacity];
	for (int i = 0; i < num; i++)
	{
		this->codes[i] = other.codes[i];
	}
}

void CodeArray::destroy()
{
	delete[] this->codes;
}

void CodeArray::resize()
{
	this->capacity *= 2;
	Code* other = new Code[capacity];
	for (int i = 0; i < this->num; i++)
		other[i] = this->codes[i];
	delete[] this->codes;
	this->codes = other;
}
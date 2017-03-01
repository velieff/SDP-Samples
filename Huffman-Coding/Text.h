#include<iostream>
#include<fstream>

#ifndef _TEXT_HEADER_
#define _TEXT_HEADER_

// I use this class instead of using char, because in class Text, I need a class which is different from char
class Symbol
{
private:
	char s;
public:
	Symbol(){ this->s = '\0'; }
	~Symbol(){}
	Symbol(const Symbol& other){ this->s = other.s; }
	Symbol(char sym){ this->s = sym; }
	Symbol(int n){ this->s = char(n); }
	Symbol(std::fstream& S){ S.read((char*)&this->s, sizeof(this->s)); }
	Symbol& operator=(const Symbol& other){ this->s = other.s; return *this; }
	Symbol& operator=(char sym){ this->s = sym; return *this; }
	Symbol& operator=(int n){ this->s = char(n); return *this; }
	void serialize(std::ostream& s){ s.write((const char*)&this->s, sizeof(this->s)); }
	operator char() const { return this->s; }
	friend std::ostream& operator<<(std::ostream& output, const Symbol& s){ return output << s.s; }
	friend std::istream& operator>>(std::istream& input, Symbol& s){ return input >> s.s; }
	bool operator==(char sym) const{ return this->s == sym; }
};

// this class is something like 'string' but it does not store char* it stores Symbol*
// I use Symbol because I can allocate more memory than I need
// if I use char* I have to resize it every time when I add a new element
class Text
{
private:
	Symbol *s;
	int num;
	int capacity;
public:
	Text();
	~Text();
	Text(const Text& other);
	Text& operator=(const Text& other);
	Text(std::fstream& S);
	Text(char* t);
	void add(const Symbol& sym);
	void add(char sym);
	void add(char* str);
	int get_size() const;
	friend std::ostream& operator<<(std::ostream& output, const Text& t);
	Symbol& operator[] (int i);
	Symbol operator[] (int i) const;
	bool empty() const;
	void serialize(std::ostream& S);
	Text& operator+=(const Text& t);
	Text operator+(const Text& t) const;
private:
	void copy(const Text& other);
	void destroy();
	void resize();
};

#endif
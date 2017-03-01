#include<iostream>
#include<fstream>

#ifndef _CODE_HEADER_
#define _CODE_HEADER_

class Code
{
private:
	char symbol;
	int frequency;
	char* code;
public:
	Code();
	~Code();
	Code(const Code& other);
	Code& operator=(const Code& other);
	Code(char S);
	Code(int F);
	Code(char S, int F, char* C);
	Code(std::istream& S);

	void set(char S, int F, char* C);
	void set_symbol(char S);
	void set_frequency(int F);
	void set_code(char* C);
	char get_symbol() const;
	int get_frequency() const;
	char* get_code() const;
	void add_to_code(char* parent_code, char x);

	friend std::ostream& operator<<(std::ostream& s, const Code& c);
	bool operator<(const Code& other) const;
	bool operator>(const Code& other) const;
	bool operator==(const Code& other) const;
	operator bool() const;
	Code& operator++();
	Code operator+(const Code& c);

	void serialize(std::ostream& S);
private:
	void initialize();
	void copy(const Code& other);
	void destroy();
};

#endif
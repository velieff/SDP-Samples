#include<iostream>
#include<fstream>
#include"Code.h"

#ifndef _CODE_ARRAY_HEADER_
#define _CODE_ARRAY_HEADER_

class CodeArray
{
private:
	Code* codes;
	int num;
	int capacity;
public:
	CodeArray();
	~CodeArray();
	CodeArray(const CodeArray& other);
	CodeArray& operator=(const CodeArray& other);
	CodeArray(std::fstream& S);
	void add(const Code& new_code);
	int find(char S) const;
	Code remove(int i);
	void add_or_increase(char S);
	Code& get_code(char S) const;
	int get_size() const;
	void set_code(char S, char* code);
	friend std::ostream& operator<<(std::ostream& output, const CodeArray& arr);
	Code& operator[] (int i) const;
	void swap(int i, int j);
	void sort();
	bool empty() const;
	void serialize(std::ostream& S);
private:
	void copy(const CodeArray& other);
	void destroy();
	void resize();
};

#endif

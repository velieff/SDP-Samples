#include<iostream>
#include<fstream>
#include"File.h"

//class for files where I store the filename, the parent directory, full address to the file and if the it's a file or directory

template <typename T>
int LEN(T t)
{
	int num = 0;
	while (t[num])
		num++;
	return num;
}

template <typename T>
void CPY(char* a, T b)
{
	int num = 0;
	while (b[num])
	{
		a[num] = b[num];
		num++;
	}
	a[num] = '\0';
}


File::File()
{
	this->filename = new char[1];
	this->filename[0] = '\0';
	this->parent = new char[1];
	this->parent[0] = '\0';
	this->full_address = new char[1];
	this->full_address[0] = '\0';
	this->file = false;
}

File::~File()
{
	destroy();
}

File::File(const File& other)
{
	copy(other);
}

File& File::operator=(const File& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

File::File(const char* Filename, const char* Parent, bool is_file)
{
	this->filename = new char[LEN<const char*>(Filename) + 1];
	CPY<const char*>(this->filename, Filename);
	this->parent = new char[LEN<const char*>(Parent) + 1];
	CPY<const char*>(this->parent, Parent);
	this->file = is_file;
	this->full_address = new char[1];
	this->full_address[0] = '\0';
}

File::File(std::istream& S)
{
	int N;
	S.read((char*)&N, sizeof(N));
	this->filename = new char[N + 1];
	S.read(this->filename, N + 1);
	S.read((char*)&this->file, sizeof(this->file));
	this->parent = new char[1];
	this->parent[0] = '\0';
	this->full_address = new char[1];
	this->full_address[0] = '\0';
}

char* File::get_filename() const
{
	return this->filename;
}

char* File::get_full_address() const
{
	return this->full_address;
}

char* File::get_parent() const
{
	return this->parent;
}

void File::concatenate_filename_with_parent()
{
	int A = LEN<char*>(this->parent);
	int B = LEN<char*>(this->filename);
	char* tmp = new char[A + B + 2];
	for (int i = 0; i < A; i++)
		tmp[i] = this->parent[i];
	tmp[A] = '\\';
	for (int j = A + 1; j < A + B + 1; j++)
		tmp[j] = filename[j - A - 1];
	tmp[A + B + 1] = '\0';
	delete[] this->filename;
	this->filename = tmp;
}

void File::concatenate_filename_with(char* x)
{
	int A = LEN<char*>(x);
	int B = LEN<char*>(this->filename);
	char* tmp = new char[A + B + 2];
	for (int i = 0; i < A; i++)
		tmp[i] = x[i];
	tmp[A] = '\\';
	for (int j = A + 1; j < A + B + 1; j++)
		tmp[j] = filename[j - A - 1];
	tmp[A + B + 1] = '\0';
	delete[] this->filename;
	this->filename = tmp;
}

void File::set(const char* Filename, const char* Parent, bool is_file)
{
	delete[] this->filename;
	this->filename = new char[LEN<const char*>(Filename) +1];
	CPY<const char*>(this->filename, Filename);
	delete[] this->parent;
	this->parent = new char[LEN<const char*>(Parent) + 1];
	CPY<const char*>(this->parent, Parent);
	this->file = is_file;
}

void File::set_parent(char* P)
{
	delete[] this->parent;
	this->parent = new char[LEN<char*>(P) + 1];
	CPY<char*>(this->parent, P);
}

void File::set_full_address(const char* FA)
{
	delete[] this->full_address;
	this->full_address = new char[LEN<const char*>(FA) + 1];
	CPY<const char*>(this->full_address, FA);
}

bool File::is_file() const
{
	return this->file;
}

void File::serialize(std::ostream& S)
{
	int N = LEN<char*>(this->filename);
	S.write((const char*)&N, sizeof(N));
	S.write(this->filename, N + 1);
	S.write((const char*)&this->file, sizeof(this->file));
}

std::ostream& operator<<(std::ostream& s, const File& f)
{
	s << f.parent << ' ' << f.filename << ' ' << (f.file ? "is file" : "is directory");
	return s;
}

void File::copy(const File& other)
{
	int N = LEN<char*>(other.filename);
	this->filename = new char[N + 1];
	CPY<char*>(this->filename, other.filename);

	N = LEN<char*>(other.parent);
	this->parent = new char[N + 1];
	CPY<char*>(this->parent, other.parent);

	N = LEN<char*>(other.full_address);
	this->full_address = new char[N + 1];
	CPY<char*>(this->full_address, other.full_address);

	this->file = other.file;
}

void File::destroy()
{
	delete[] this->filename;
	delete[] this->parent;
	delete[] this->full_address;
}
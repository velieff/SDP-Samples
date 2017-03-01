#include<iostream>
#include<fstream>

#ifndef _FILE_HEADER_
#define _FILE_HEADER_

//class for files where I store the filename, the parent directory, full address to the file and if the it's a file or directory
class File
{
private:
	char* filename;
	char* parent;
	char* full_address;
	bool file;
	void copy(const File& other);
	void destroy();
public:
	File();
	~File();
	File(const File& other);
	File& operator=(const File& other);
	
	File(const char* Filename, const char* Parent, bool is_file);
	File(std::istream& S);

	char* get_filename() const;
	char* get_full_address() const;
	char* get_parent() const;

	void concatenate_filename_with_parent();
	void concatenate_filename_with(char* x);
	void set(const char* Filename, const char* Parent, bool is_file);
	void set_parent(char* P);
	void set_full_address(const char* FA);
	bool is_file() const;
	void serialize(std::ostream& S);
	friend std::ostream& operator<<(std::ostream& s, const File& f);
};

#endif
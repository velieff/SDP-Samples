#include<iostream>
#include<fstream>
#include<filesystem>
#include"HuffmanTree.h"
#include"CodeArray.h"
#include"Text.h"
#include"File.h"

const int MAX_SIZE = 256;

template<typename T>
int len(T t)
{
	int num = 0;
	while (t[num])
		num++;
	return num;
}

int absolute(int n)
{
	return (n < 0 ? n * (-1) : n);
}

bool command_is(char* command, char* str)
{
	int n = 0;
	while (str[n])
	{
		if (command[n] != str[n] && absolute(int(command[n]) - int(str[n])) != 32)
			return false;
		n++;
	}
	return true;
}

char** get_paths(char* command)
{
	int N = len<char*>(command), num = 0;
	char** path = new char*[2];
	for (int i = 0; i < N; i++)
	{
		if (command[i + 1] == ':' && command[i + 2] == '\\')
		{
			int size = 0;
			while (command[i + size + 2] != ':' && i + size < N)
				size++;
			path[num] = new char[size + 1];
			for (int j = 0; j < size; j++)
				path[num][j] = command[i + j];
			path[num][size] = '\0';
			num++;
			i += size;
		}
	}
	while (num < 2) // if command is "list" or it's an invalid one
	{
		path[num] = new char[1];
		path[num][0] = '\0';
		num++;
	}
	return path;
}

void release_memory(char**& str, int size)
{
	for (int i = 0; i < size; i++)
		delete[] str[i];
	delete[] str;
	str = NULL;
}

bool are_different(char* a, const char* b)
{
	int N = len<char*>(a);
	if (N != len<const char*>(b))
		return true;
	for (int i = 0; i < N; i++)
	{
		if (a[i] != b[i])
			return true;
	}
	return false;
}

// https://msdn.microsoft.com/en-us/library/hh874743.aspx
// I used this page to help myself with the recursive_directory_iterator.
// function returns all files in that directory.
File* get_all_files_from_directory(char* directory, int& FILES)
{
	std::tr2::sys::path main_dir(directory);
	File* files = new File[MAX_SIZE];
	FILES = 0;
	for (std::tr2::sys::recursive_directory_iterator next(directory), end; next != end; ++next)
	{
		files[FILES].set(next->path().filename().c_str(), next->path().parent_path().filename().c_str(), std::tr2::sys::is_regular_file(next->path()));
		files[FILES].set_full_address(next->path().string().c_str());
		if (are_different(files[FILES].get_parent(), main_dir.filename().c_str()))
			files[FILES].concatenate_filename_with_parent();
		FILES++;
	}
	return files;
}

// returns true - if directory is NOW created.
// returns false - if directory ALREADY exists.
bool create_directory(char* directory)
{
	return std::tr2::sys::create_directories(std::tr2::sys::path(directory));
}

char** read_from_file(char* filename, int& ROWS)
{
	std::ifstream input;
	input.open(filename);
	if (input.is_open())
	{
		char** str = new char*[MAX_SIZE];
		ROWS = 0;
		while (!input.eof() && ROWS < MAX_SIZE)
		{
			str[ROWS] = new char[MAX_SIZE];
			input.getline(str[ROWS], MAX_SIZE);
			ROWS++;
		}
		input.close();
		return str;
	}

	return NULL;
}

// builds a codearray with all symbols and sets their frequencies
CodeArray build_codearray(char** str, int ROWS)
{
	CodeArray arr;
	for (int I = 0; I < ROWS; I++)
	{
		int N = len<char*>(str[I]);
		for (int i = 0; i < N; i++)
			arr.add_or_increase(str[I][i]);
		if (I != (ROWS - 1))
			arr.add_or_increase('\n');
	}
	arr.sort();
	return arr;
}

// converts char* to Text using the code array
Text str_to_text(char** str, int ROWS, CodeArray& arr)
{
	Text text;
	int N;
	for (int I = 0; I < ROWS; I++)
	{
		N = len<char*>(str[I]);
		for (int j = 0; j < N; j++)
			text.add(arr.get_code(str[I][j]).get_code());

		if (I != (ROWS - 1))
			text.add(arr.get_code('\n').get_code());
	}
	return text;
}

// main function for packing files
void pack(char* directory, char* archivename)
{
	std::cout << "Packing...\n";
	int ROWS = 0, FILES = 0, N = 0;
	File* files = get_all_files_from_directory(directory, FILES);
	char** str = NULL;

	std::fstream file(archivename, std::ios::out | std::ios::binary);
	file.write((const char*)&FILES, sizeof(FILES));
	for (int i = 0; i < FILES; i++)
		files[i].serialize(file);

	for (int i = 0; i < FILES; i++)
	{
		if (files[i].is_file())
		{
			str = read_from_file(files[i].get_full_address(), ROWS);
			if (str)
			{
				CodeArray arr(build_codearray(str, ROWS));
				HuffmanTree tree;
				tree.build_pack(arr);
				tree.copy_codes_to_arr(arr);
				Text text(str_to_text(str, ROWS, arr));
				arr.serialize(file);
				text.serialize(file);

				release_memory(str, ROWS);
				std::cout << files[i].get_filename() << " - the file is successfully packed!\n";
			}
			else
				std::cout << files[i].get_filename() << " - the file is not packed! Error while reading.\n";
		}
		else // directory
			std::cout << files[i].get_filename() << " - the directory is successfully packed!\n";

	}
	file.close();

	delete[] files;

	std::cout << "Packing successfully finished!\n";
}

// main function for unpacking files
void unpack(char* archivename, char* directory)
{
	std::fstream file(archivename, std::ios::in | std::ios::binary);
	if (!file)
	{
		std::cout << archivename << " - the file is not valid!\n";
		return;
	}
	std::cout << "Unpacking...\n";
	if (create_directory(directory))
		std::cout << directory << " - the directory is successfully created!\n";
	int FILES = 0, N = 0;
	file.read((char*)&FILES, sizeof(FILES));
	File* files = new File[FILES + 1];
	
	for (int i = 0; i < FILES; i++)
	{
		files[i] = File(file);
		files[i].set_parent(files[i].get_filename()); // I USE THIS FOR STORING THE ORIGINAL FILENAME (BECAUSE AFTER THAT I CONCATENATE IT)
		files[i].concatenate_filename_with(directory);
	}

	for (int i = 0; i < FILES; i++)
	{
		if (files[i].is_file())
		{
			CodeArray arr(file);
			Text binary(file);
			HuffmanTree tree;
			tree.build_unpack(arr);
			Text unpacked(tree.unpack_text(binary));

			std::ofstream output;
			output.open(files[i].get_filename());
			output << unpacked;
			output.close();
			std::cout << files[i].get_parent() << " - the file is successfully unpacked!\n";
		}
		else
		{
			create_directory(files[i].get_filename());
			std::cout << files[i].get_parent() << " - the directory is successfully unpacked!\n";
		}
	}
	file.close();

	delete[] files;

	std::cout << "Unpacking successfully finished!\n";
}

// prints the list of the files in the archive
void list(char* archivename)
{
	std::fstream file(archivename, std::ios::in | std::ios::binary);
	if (!file)
	{
		std::cout << archivename << " - the file is not valid!\n";
		return;
	}
	std::cout << "List:\n";
	int FILES = 0, N = 0;
	file.read((char*)&FILES, sizeof(FILES));
	File* files = new File[FILES + 1];

	for (int i = 0; i < FILES; i++)
	{
		files[i] = File(file);
		std::cout << i + 1 << ": " << files[i].get_filename() << (files[i].is_file() ? " - file\n" : " - directory\n");
	}
	file.close();

	delete[] files;
}

/**
*
*	File Archiver
*	Huffman Coding
*
*	Data Structures Course
*	Solution to course project
*	Faculty of Mathematics and Informatics of Sofia University
*	Winter semester 2016/2017
*
*	Created By Merhat Veliev
*	https://github.com/velieff/Huffman-Coding
*
*/

/**
*
*	VALID COMMANDS:
*	1) pack <directory> <archivename> - builds an archive with name <archivename>, where are packed the files and directories from <directory>
*	2) unpack <archivename> <directory> - unpacks <archivename> to the folder <directory>
*	3) list <archivename> - prints the list of the files and directories, which are packed in <archivename>
*
*/

#include<iostream>
#include"MainFunctions.h"

int main(int argc, char* argv[])
{
	std::cout << "File Archiver\nHuffman Coding\nCreated By Merhat Veliev\n\n";
	char** path = NULL;
	for (int i = 1; argv[i]; i++)
	{
		path = get_paths(argv[i]);

		if (command_is(argv[i], "pack"))
			pack(path[0], path[1]);

		else if (command_is(argv[i], "unpack"))
			unpack(path[0], path[1]);

		else if (command_is(argv[i], "list"))
			list(path[0]);

		else
			std::cout << "Invalid command!\n";

		release_memory(path, 2);
	}

	return 0;
}
#include<iostream>
#include"Code.h"
#include"CodeArray.h"
#include"Queue.h"
#include"Text.h"

#ifndef _HUFFMAN_TREE_HEADER_
#define _HUFFMAN_TREE_HEADER_

class Box
{
public:
	Code data;
	Box *left, *right;
	Box() { data = Code(); left = NULL; right = NULL; }
	Box(const Code& D) { data = D; left = NULL; right = NULL; }
	Box(const Code& D, Box* L, Box* R) { data = D; left = L; right = R; }
};

class HuffmanTree
{
private:
	Box* root;

public:
	HuffmanTree();
	~HuffmanTree();
	HuffmanTree(const HuffmanTree& other);
	HuffmanTree& operator=(const HuffmanTree& other);

	HuffmanTree(const Code& Root);
	HuffmanTree(const Code& L, const Code& R);
	HuffmanTree(const HuffmanTree& L, const HuffmanTree& R);
	HuffmanTree(const Code& Root, const Code& L, const Code& R);

	void build_pack(CodeArray& arr); // builds tree while packing
	void build_unpack(CodeArray& arr); // builds tree while unpacking
	void copy_codes_to_arr(CodeArray& arr); // copies all the codes from tree to array

	Text unpack_text(Text& binary); // converts binary text to normal text using the tree

private:
	void add_to_left_and_set_new_root(const Code& L); // adds the 'L' to *left and the old root to *right and sets new root
	void add_to_right_and_set_new_root(const Code& R); // adds the 'R' to *right and the old root to *left and sets new root
	void add_two_trees_and_set_new_root(const HuffmanTree& L, const HuffmanTree& R); // adds tree 'L' to *left, tree 'R' to *right and sets new root
	void add_with_code(Box*& Root, char* code, int i, int len, const Code& element); // help function for building tree while unpacking
	void set_codes(Box* Root); // sets codes - to left edges adds '0' and to right edges adds '1'
	void cpy_codes(Box* Root, CodeArray& arr); // help function for copying codes
	void get_symbols_with_code(Box*& Root, Text& binary, Text& unpacked, int i, int binary_len); // help function for building tree while unpacking 
	bool is_leaf(const Box* Root) const; // checks if a Box* is leaf from the tree
	Box* copy(Box* Root); // copies one tree's boxes(Box*) to an other tree
	void destroy(Box* Root); // destroys the tree
	void initialize(); // sets the root to null (by default)
};

#endif
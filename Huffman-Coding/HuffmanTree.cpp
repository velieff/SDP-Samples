#include<iostream>
#include"Code.h"
#include"CodeArray.h"
#include"HuffmanTree.h"
#include"Queue.h"

HuffmanTree::HuffmanTree()
{
	initialize();
}

HuffmanTree::~HuffmanTree()
{
	destroy(this->root);
	initialize();
}

HuffmanTree::HuffmanTree(const HuffmanTree& other)
{
	this->root = copy(other.root);
}

HuffmanTree& HuffmanTree::operator=(const HuffmanTree& other)
{
	if (this != &other)
	{
		destroy(this->root);
		this->root = copy(other.root);
	}
	return *this;
}

HuffmanTree::HuffmanTree(const Code& Root)
{
	this->root = new Box(Root);
}

HuffmanTree::HuffmanTree(const Code& L, const Code& R)
{
	this->root = new Box(Code(L.get_frequency() + R.get_frequency()), new Box(L), new Box(R));
}

HuffmanTree::HuffmanTree(const HuffmanTree& L, const HuffmanTree& R)
{
	this->root = new Box(Code(L.root->data.get_frequency() + R.root->data.get_frequency()), copy(L.root), copy(R.root));
}

HuffmanTree::HuffmanTree(const Code& Root, const Code& L, const Code& R)
{
	this->root = new Box(Root, new Box(L), new Box(R));
}

int Len(char* t)
{
	int num = 0;
	while (t[num])
		num++;
	return num;
}

// sets codes - to left edges adds '0' and to right edges adds '1'
void HuffmanTree::set_codes(Box* Root)
{
	if (Root->left)
	{
		Root->left->data.add_to_code(Root->data.get_code(), '0');
		set_codes(Root->left);
	}

	if (Root->right)
	{
		Root->right->data.add_to_code(Root->data.get_code(), '1');
		set_codes(Root->right);
	}
}

// adds all array elements to the queue
void array_to_queue(CodeArray& arr, Queue<Code>& q)
{
	for (int i = 0; i < arr.get_size(); i++)
		q.enqueue(arr[i]);
}

// builds tree while packing
void HuffmanTree::build_pack(CodeArray& arr)
{
	Queue<Code> q;
	array_to_queue(arr, q);


	if (q.size() > 4)
	{
		HuffmanTree tree1(q.dequeue(), q.dequeue());
		HuffmanTree tree2(q.dequeue(), q.dequeue());
		while (q.size() > 1)
		{
			tree1.add_to_left_and_set_new_root(q.dequeue());
			if (q.size() > 1)
				tree2.add_to_right_and_set_new_root(q.dequeue());
		}
		add_two_trees_and_set_new_root(tree1, tree2);
		add_to_right_and_set_new_root(q.dequeue());
	}
	else if (q.size() > 0)
	{
		if (q.size() == 1)
		{
			destroy(this->root);
			this->root = new Box(Code(), NULL, new Box(q.dequeue()));
		}
		else
		{
			HuffmanTree tree(q.dequeue());
			while (q.size() > 1)
				tree.add_to_left_and_set_new_root(q.dequeue());
			tree.add_to_right_and_set_new_root(q.dequeue());
			*this = tree;
		}
	}
	else
		return;

	set_codes(this->root);
}

// builds tree while unpacking
void HuffmanTree::build_unpack(CodeArray& arr)
{
	int N;
	for (int i = 0; i < arr.get_size(); i++)
	{
		N = Len(arr[i].get_code());
		add_with_code(this->root, arr[i].get_code(), 0, N, arr[i]);
	}
}

// copies all the codes from tree to array
void HuffmanTree::copy_codes_to_arr(CodeArray& arr)
{
	cpy_codes(this->root, arr);
}

// converts binary text to normal text using the tree
Text HuffmanTree::unpack_text(Text& binary)
{
	Text unpacked;
	int binary_len = binary.get_size();
	get_symbols_with_code(this->root, binary, unpacked, 0, binary_len);
	return unpacked;
}

// help function for building tree while unpacking
void HuffmanTree::add_with_code(Box*& Root, char* code, int i, int len, const Code& element)
{
	if (Root == NULL)
		Root = new Box(Code());
	
	if (i == len - 1)
	{
		if (code[i] == '0')
			Root->left = new Box(element);
		else if (code[i] == '1')
			Root->right = new Box(element);
	}
	else if (i < (len - 1))
	{
		if (code[i] == '0')
			add_with_code(Root->left, code, i + 1, len, element);
		else if (code[i] == '1')
			add_with_code(Root->right, code, i + 1, len, element);
	}

}

// adds the 'L' to *left and the old root to *right and sets new root
void HuffmanTree::add_to_left_and_set_new_root(const Code& L)
{
	Box* box = new Box(this->root->data + L, new Box(L), copy(this->root));
	destroy(this->root);
	this->root = box;
}

// adds the 'R' to *right and the old root to *left and sets new root
void HuffmanTree::add_to_right_and_set_new_root(const Code& R)
{
	Box* box = new Box(this->root->data + R, copy(this->root), new Box(R));
	destroy(this->root);
	this->root = box;
}

// adds tree 'L' to *left, tree 'R' to *right and sets new root
void HuffmanTree::add_two_trees_and_set_new_root(const HuffmanTree& L, const HuffmanTree& R)
{
	destroy(this->root);
	this->root = new Box(L.root->data + R.root->data, copy(L.root), copy(R.root));
}

// help function for copying codes
void HuffmanTree::cpy_codes(Box* Root, CodeArray& arr)
{
	if (Root->left)
	{
		if (is_leaf(Root->left))
			arr.set_code(Root->left->data.get_symbol(), Root->left->data.get_code());
		cpy_codes(Root->left, arr);
	}

	if (Root->right)
	{
		if (is_leaf(Root->right))
			arr.set_code(Root->right->data.get_symbol(), Root->right->data.get_code());
		cpy_codes(Root->right, arr);
	}
}

// help function for building tree while unpacking 
void HuffmanTree::get_symbols_with_code(Box*& Root, Text& binary, Text& unpacked, int i, int binary_len)
{
	if (i == binary_len + 1)
		return;
	if (is_leaf(Root))
	{
		unpacked.add(Root->data.get_symbol());
		get_symbols_with_code(this->root, binary, unpacked, i, binary_len);
	}
	else if (binary[i] == '0')
		get_symbols_with_code(Root->left, binary, unpacked, i + 1, binary_len);
	else if (binary[i] == '1')
		get_symbols_with_code(Root->right, binary, unpacked, i + 1, binary_len);
}

// checks if a Box* is leaf from the tree
bool HuffmanTree::is_leaf(const Box* Root) const
{
	return (Root->left == NULL) && (Root->right == NULL);
}

// copies one tree's boxes(Box*) to an other tree
Box* HuffmanTree::copy(Box* Root)
{
	if (Root)
		return new Box(Root->data, copy(Root->left), copy(Root->right));
	else
		return NULL;
}

// destroys the tree
void HuffmanTree::destroy(Box* Root)
{
	if (Root)
	{
		destroy(Root->left);
		destroy(Root->right);
		delete Root;
	}
}

// sets the root to null (by default)
void HuffmanTree::initialize()
{
	this->root = NULL;
}
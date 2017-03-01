/**
*
*	Binary Search Tree Implementation
*	Created By Merhat Veliev
*	https://github.com/velieff/SDP-Samples/blob/master/BinarySearchTree/BSTree.h
*
*/

#ifndef _BSTREE_HEADER_
#define _BSTREE_HEADER_

#include<iostream>
#include<fstream>

template<class T>
class BSTree
{
private:
	class Box
	{
	public:
		T data;
		Box *left, *right;
		Box() { data = T(); left = NULL; right = NULL; }
		Box(const T& D) { data = D; left = NULL; right = NULL; }
		Box(const T& D, Box* L, Box* R) { data = D; left = L; right = R; }
	};

	Box *root;

public:
	BSTree()
	{
		initialize();
	}

	~BSTree()
	{
		destroy(this->root);
		initialize();
	}

	BSTree(const BSTree& other)
	{
		this->root = copy(other.root);
	}
	BSTree& operator=(const BSTree& other)
	{
		if (this != &other)
		{
			destroy(this->root);
			this->root = copy(other.root);
		}
		return *this;
	}

	void add(const T& element)
	{
		add_hf(this->root, element);
	}

	bool remove(const T& element)
	{
		return remove_hf(this->root, element);
	}
	bool search(const T& element)
	{
		return search_hf(this->root, element);
	}
	
private: // HELP FUNCTIONS (HF)
	void add_hf(Box*& r, const T& e)
	{
		if (r == NULL)
			r = new Box(e);
		else
		{
			if (e < r->data)
				add_hf(r->left, e);
			else if (e == r->data)
				return;
			else
				add_hf(r->right, e);
		}
	}
	bool remove_hf(Box*& r, const T& e)
	{
		if (r == NULL)
			return false;
		else if (r->data == e)
		{
			Box* del = r;
			if (r->left == NULL)
				r = r->right;
			else if (r->right == NULL)
				r = r->left;
			else
			{
				Box* tmp = r->left;
				while (tmp->right != NULL)
					tmp = tmp->right;
				tmp->left = r->left;
				tmp->right = r->right;
				r = tmp;

			}
			delete del;
			del = NULL;

			return true;
		}
		else
		{
			if (e < r->data)
				return remove_hf(r->left, e);
			else
				return remove_hf(r->right, e);
		}
	}
	bool search_hf(Box* r, const T& e)
	{
		if (r == NULL)
			return false;
		else if (r->data == e)
			return true;
		else if (e < r->data)
			return search_hf(r->left, e);
		else
			return search_hf(r->right, e);
	}

private:
	void initialize()
	{
		this->root = NULL;
	}
	Box* copy(Box* r)
	{
		if (r)
			return new Box(r->data, copy(r->left), copy(r->right));
		else
			return NULL;
	}
	void destroy(Box* r)
	{
		if (r)
		{
			destroy(r->left);
			destroy(r->right);
			delete r;
		}
	}
};

#endif

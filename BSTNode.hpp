

#ifndef BSTNODE_HPP_
#define BSTNODE_HPP_

#include <iostream>
#include <cstdlib>
#include "Book.hpp"
using namespace std;

class BSTNode{
	friend class BST;
	friend class Library;
	BSTNode *left;
	BSTNode *right;
	BSTNode *parent;
	Book *book;
	int height;
public:
	BSTNode(string t, string auth, int yr, string pub, long long isbn, float rate);
	BSTNode();
	~BSTNode();
	void printNode(bool debug); // prints information about the node and data, nicely formatted
								// only prints the node's information if called with debug set to true
};




#endif /* BSTNODE_HPP_ */

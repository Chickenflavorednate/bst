

#include <iostream>
#include <string>
#include "BSTNode.hpp"
using namespace std;

BSTNode::BSTNode (string t, string auth, int yr, string pub, long long isbn, float rate) {
	book = new Book(t, auth, yr, pub, isbn, rate);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 1;
}
BSTNode::BSTNode() {
    book = nullptr;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
}

BSTNode::~BSTNode(){
	cout <<"Deleting "<<book->title<<endl;
	delete book;
	book = NULL;
}

void BSTNode::printNode(bool debug) {
	/* takes a boolean to decide whether to print extra information about the node - useful for debugging */
	book->printBook();
	if(debug) {
		cout << "Node: h=" << height ;
		cout << "\n\tParent: " << (parent ? parent->book->title + ": " + parent->book->author : "NODE IS ROOT");
		cout << "\n\tLeft: " << (left ? left->book->title + ": " + left->book->author : "--");
		cout << "\n\tRight: " << (right ? right->book->title + ": " + right->book->author : "--");
		cout << endl << endl;
	}
}




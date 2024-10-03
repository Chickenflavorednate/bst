#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() {
	root = nullptr;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
    root = new BSTNode(title, author, yr, pub, isbn, rate);
    setHeight(root);
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode *current = root;
    BSTNode *prev = nullptr;
    BSTNode *newNode = new BSTNode(title, author, yr, pub, isbn, rate);

    if(root == nullptr){
        root = newNode;
        return;
    }

    while(current != nullptr){
        prev = current;
        if(*newNode -> book < *current -> book){
            current = current -> left;
        }
        else{
            current = current -> right;
        }
    }
    newNode -> parent = prev;

    if(*newNode -> book < *prev -> book){
        prev -> left = newNode;
    }
    else{
        prev -> right = newNode;
    }

    setHeight(newNode);
}


BSTNode *BST::find(string title, string author) {
    return find(title, author, root);
}

BSTNode *BST::find(string title, string author, BSTNode *start) {
    if(start == nullptr){
        return nullptr;
    }

    //if((start->book->title == title) && (start->book->author == author)){
    if(title == start->book->title && author == start->book->author){
        return start; //found
    }
    //else if(start->book->author > author){
    else if(author < start->book->author || (author == start->book->author && title < start->book->title)){
        return find(title, author, start -> left);
    }
    else{
        return find(title, author, start -> right);
    }
}


void BST::printTreeIO() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing In-Order:" << endl;
		printTreeIO(root);
	}
}

void BST::printTreeIO(BSTNode *node) {
    if(node != nullptr){
        printTreeIO(node -> left);
        node -> printNode(false);
        printTreeIO(node -> right);
    }
}

void BST::printTreePre() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing Pre-Order:" << endl;
		printTreePre(root);
	}
}

void BST::printTreePre(BSTNode *node) {
    if(node != nullptr){
        node -> printNode(false);
        printTreeIO(node -> left);
        printTreeIO(node -> right);
    }
}

void BST::printTreePost() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing Post-Order:" <<endl;
		printTreePost(root);
	}
}

void BST::printTreePost(BSTNode *node) {
    if(node != nullptr){
        printTreeIO(node -> left);
        printTreeIO(node -> right);
        node -> printNode(false);
    }
}

void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(BSTNode *node) {
	if (node == NULL) {
		return;
	}
	else {
		clearTree(node->left);
		node->left = NULL;
		clearTree(node->right);
		node->right = NULL;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
    BSTNode *bookWanted = find(title, author);

    if(bookWanted == nullptr){
        return false; //no book
    }

    if(!bookWanted -> book -> checked_out){
        bookWanted -> book -> checked_out = true;
        return true;
    }
    else{
        return false; //book alrdy checked out
    }
}

bool BST::checkIn(string title, string author) {
    BSTNode *bookWanted = find(title, author);

    if(bookWanted == nullptr){
        return false; //no book
    }

    if(bookWanted -> book -> checked_out){
        bookWanted -> book -> checked_out = false;
        return true;
    }
    else{
        return false; //book alrdy checked in
    }
}

void BST::updateRating(string title, string author, float newRating) {
	BSTNode *tmp = find(title, author);

    if(tmp == nullptr){
        return; //no book
    }
    else{
        tmp-> book -> rating = newRating;
    }

}


BSTNode *BST::removeNoKids(BSTNode *node) {
    BSTNode *temp = node;

    if(node == root){
        root = nullptr;
        return temp;
    }

    if(node -> parent -> left == node){
        node -> parent -> left = nullptr;
    }
    else{
        node -> parent -> right = nullptr;
    }

    setHeight(node -> parent);
    delete node;
    return temp;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    BSTNode *child;

	if(node == nullptr){
        return nullptr;
    }

    if(leftFlag){
        child = node -> left;
    }
    else{
        child = node -> right;
    }

    if(node -> parent == nullptr){
        //if node is root
        root = child;
        if(child != nullptr){
            child -> parent = nullptr;
        }
    }
    else if(node -> parent -> left == node){
        // node is the left child
        node -> parent = child;
        if(child != nullptr){
            child -> parent = node ->parent;
        }
    }
    else{
        //node is right child
        node -> parent = child;
        if(child != nullptr){
            child-> parent = node -> parent;
        }
    }

    setHeight(node -> parent);
    delete node;
    return child;
}

BSTNode *BST::remove(string title, string author) {
	BSTNode *current = find(title, author);

    if(current -> left == nullptr && current -> right == nullptr){
        removeNoKids(current);
    }
    else if(current -> left == nullptr || current -> right == nullptr){
        if(current -> left == nullptr){
            removeOneKid(current, false);
        }
        else{
            removeOneKid(current, true);
        }

    }
    else{
        BSTNode *replacement = current -> right;
        BSTNode *replacementParent = current;

        while(replacement -> left != nullptr){
            // finding the minimum left most value in the right subtree
            replacementParent = replacement;
            replacement = replacement -> left;
        }

        current -> book = replacement -> book;
        replacement -> parent = current -> parent;
        //do i need to set curr parent to new node parent?


        if(replacementParent == current){
            //
            if(replacement -> right != nullptr){
                replacement -> right -> parent = replacementParent;
                replacementParent -> right = replacement -> right;
            }
        }
        else{
            if(replacement -> left != nullptr){
                replacement -> left -> parent = replacementParent;
                replacementParent -> left = replacement -> left;
            }
        }

        setHeight(replacementParent);
        delete replacement;
        return current;
    }
}

void BST::setHeight(BSTNode *node) {
    int leftHeight = 0;
    int rightHeight = 0;

    if (node == nullptr) {
        return;
    }

    setHeight(node -> left);
    setHeight(node -> right);


    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }

    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }

    int newHeight = 1 + std::max(leftHeight, rightHeight);
    node -> height = newHeight;
}

//if (node == nullptr) {
//return;
//}
//
//setHeight(node -> left);
//setHeight(node -> right);
//
//int leftHeight = 0;
//int rightHeight = 0;
//
//if (node->left != nullptr) {
//leftHeight = node->left->height;
//}
//
//if (node->right != nullptr) {
//rightHeight = node->right->height;
//}
//
//node->height = 1 + std::max(leftHeight, rightHeight);
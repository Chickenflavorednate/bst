#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#include <iostream>
#include <cstdlib>
#include "BST.hpp"
using namespace std;

class Library {
	string filename;
	BST *tree;
public:
	Library(string filename);
	void readFile();
	void strip(string s,  string arr[]);
	void menu();
	void getInfo(string& title, string& author);
	void search(bool debug);
	void checkIn();
	void checkOut();
	void updateRating();
	void addBook();
	void removeBook();
	void browseCatalog();
};




#endif /* LIBRARY_HPP_ */

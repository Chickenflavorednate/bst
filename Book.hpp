#ifndef BOOK_HPP_
#define BOOK_HPP_

#include <iostream>
#include <cstdlib>
using namespace std;

class Book {
	friend class BSTNode;
	friend class BST;
	// friend class Library;
	string title;
	string author;
	int year;           // year of publication
	string publisher;   //
	long long isbn13;   // 13 digits is too long to fit in an int or a long
	float rating;
	bool checked_out;
public:
	Book(string t, string auth, int yr, string pub, long long isbn, float rate);
	Book();
	float getRating();
	void printBook();
	bool operator<(Book b2);
	bool operator>(Book b2);
	bool operator==(Book b2);
	bool operator!=(Book b2);
	bool operator<=(Book b2);
	bool operator>=(Book b2);
};




#endif /* BOOK_HPP_ */

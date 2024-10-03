#include "Book.hpp"

#include <iostream>
#include <string>
using namespace std;


Book::Book(string t, string auth, int yr, string pub, long long isbn, float rate) {
	title = t;
	author = auth;
	year = yr;
	publisher = pub;
	isbn13 = isbn;
	rating = rate;
	checked_out = false;
}

Book::Book() {
	title = "";
	author = "";
	year = 0;
	publisher = "";
	isbn13 = 0;
	rating = 0;
	checked_out = false;
}

float Book::getRating() {
	return rating;
}


void Book::printBook() {
	cout << "---------------------" << endl;
	cout << title << "\nAuthor: " << author << "\t\tYear: " << year << endl;
	cout << "Publisher: " << publisher << "\tISBN-13: " << isbn13 << "\tRating: " << rating << endl;
	cout << "Currently Available: " << (checked_out ? "No" : "Yes") << endl;
}

bool Book::operator<(Book b2) {
    if(author < b2.author){
        return true;
    }
    else if(author == b2.author){
        return title < b2.title;
    }
    return false;
}

bool Book::operator>(Book b2) {
    if(author > b2.author){
        return true;
    }
    else if(author == b2.author){
        return title > b2.title;
    }
    return false;
}

bool Book::operator==(Book b2) {
    if((author == b2.author) && (title == b2.title)){
        return true;
    }
    return false;
}

bool Book::operator!=(Book b2) {
    return !(operator==(b2));
}

bool Book::operator<=(Book b2) {
    return operator<(b2) || operator==(b2);
}

bool Book::operator>=(Book b2) {
    return operator>(b2) || operator==(b2);
}
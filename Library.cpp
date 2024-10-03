#include "Library.hpp"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


Library::Library(string name) {
	filename = name;
	tree = new BST();
	readFile();
}


void Library::menu() {
	int choice = -1;
	while(choice) {
		cout << endl << endl << "Choose an option:\n\t1. Find a book\n\t2. Check out a book\n\t3. Return a book" << endl;
		cout << "\t4. Update the rating for a book" << endl;
		cout << "\t5. Add a book to the catalog\n\t6. Retire a book from the catalog\n\t7. Print the catalog" << endl;
		cout << "\t8. Print a node with debugging info\n\t0. Quit" << endl << endl;
		cin >> choice;
		switch (choice) {
			case 1:
				search(false);
				break;
			case 2:
				checkOut();
				break;
			case 3:
				checkIn();
				break;
			case 4:
				updateRating();
				break;
			case 5:
				addBook();
				break;
			case 6:
				removeBook();
				break;
			case 7:
				browseCatalog();
				break;
			case 8:
				search(true);
				break;
			case 0:
				delete tree;
				cout << "Goodbye!" << endl;
				break;
			default:
				cout << "Invalid option.  Try again." << endl;
		}
	}
}

void Library::getInfo(string &title, string &author) {
	cin.ignore();
	cout << "What is the title of the book you are looking for?" << endl;
	getline(cin, title);
	cout << "Who is the author? Please enter Last Name, First Name Middle Name" << endl;
	getline(cin, author);
}

void Library::search(bool debug) {
	string title;
	string author;
	getInfo(title, author);
	BSTNode* found = tree->find(title, author);
	if (found) {
		found->printNode(debug);
	}
	else {
		cout << "Sorry, we do not have that book." << endl;
	}
}

void Library::checkIn() {
	string title;
	string author;
	getInfo(title, author);
	bool result = tree->checkIn(title, author);
	if(result) {
		cout << "Book returned!" << endl;
	}
	else {
		cout << "Error: all books were already returned" << endl;
	}
}

void Library::checkOut() {
	string title;
	string author;
	getInfo(title, author);
	bool result = tree->checkOut(title, author);
	if(result) {
		cout << "We hope you enjoy the book!" << endl;
	}
	else {
		cout << "Error: no copies of " << title << " are available" << endl;
	}
}

void Library::updateRating() {
	string title, author;
	getInfo(title, author);
	BSTNode* tmp = tree->find(title, author);
	if (tmp) {
		cout << "The current rating for " << title << " by " << author << " is " << tmp->book->getRating() << endl;
		cout << "Enter a new rating:" << endl;
		string rating;
		getline(cin, rating);
		tree->updateRating(title, author, stof(rating));
		cout << "Rating updated!" << endl;
	}
	else { // book not found
		cout << "Error: the book was not found." << endl;
	}
}

void Library::addBook() {
	string title;
	string author;
	string year;
	string pub;
	string isbn;
	string rating;
	cin.ignore();
	cout << "Please enter the book's information:\n\tTitle: ";
	getline(cin,title);
	cout << "\tAuthor: ";
	getline(cin, author);
	cout << "\tPublication year: ";
	getline(cin, year);
	cout << "\tPublisher: ";
	getline(cin, pub);
	cout << "\tISBN-13: ";
	getline(cin, isbn);
	cout << "Rating: ";
	getline(cin, rating);
	cout << "Adding: " << title << ": " << author << endl;
	tree->insert(title, author, stoi(year), pub, stoll(isbn), stof(rating));
}

void Library::removeBook() {
	string title;
	string author;
	cout << "Please enter the information for the book you want to remove." << endl;
	getInfo(title, author);
	BSTNode* book = tree->remove(title, author);
	if(book) {
		cout << "Removing: ";
		book->book->printBook();
		delete book;
	}
	else {
		cout << title << ": " << author << " not found!" << endl;
	}
}

void Library::browseCatalog() {
	int choice = 0;
	cout << "Select an option:\n\t1. Pre-order print\n\t2. In-order print\n\t3. Post-order print" << endl;
	cin >> choice;
	switch(choice) {
		case 1:
			tree->printTreePre();
			break;
		case 2:
			tree->printTreeIO();
			break;
		case 3:
			tree->printTreePost();
			break;
		default:
			cout << "Invalid option." << endl;
	}
}

void Library::strip(string s, string arr[]) {
	const char* Splitter = "|";
	const char* EndChar = "|";
	size_t start = 0;
	int len;
	for (int i = 0; i < 6; i++) {
		len = s.length();
		s = s.substr(start,len-start+1);
		size_t end = s.find_first_of(EndChar);
		s = s.substr(start,len-start+1);
		end = s.find_first_of(EndChar);
		if (end > 0){
			arr[i] = s.substr(0,end);
			s = s.substr(end+1, len-end);
		}
	}
	return;
}

void Library::readFile() {
	ifstream file(filename.c_str());
	string arr[6];
	string line;
	getline(file,line);
	while (!file.eof()) {
		strip(line, arr);
		// isbn, title, author, publisher, year, rating
		cout << "Adding: " << arr[0] << ", " << arr[1] << ", " << arr[2] << ", " << arr[3];
		cout << ", " << arr[4] << ", " << arr[5] << endl;
		// title, author, year, publisher, isbn, rating
		tree->insert(arr[1], arr[2], stoi(arr[4]), arr[3], stoll(arr[0]), stof(arr[5]));
		getline(file,line);
	}
	tree->printTreeIO();
}
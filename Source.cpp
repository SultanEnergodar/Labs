#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;


enum BookType { Fiction, NoFiction };


class Book {

public:
	
	Book(const string& author, const string& title, BookType type) :_author(author), _title(title), _type(type) {};
	virtual ~Book() {};
	BookType getType() const { return _type; };
	string GetAuthor() const { return _author; };
	string GetTitle() const { return _title; };

private:
	
	string _author;
	string _title;
	BookType _type;
};


class Library {

public:

	void addBook(const string& author, const string& title, const BookType& type) {
		if (author.empty() or title.empty()) {
			cout << "error" << endl;
		}
		books.push_back(Book(author, title, type));
	};
	
	vector <Book> books;

};


void countBooksSwitch(const vector <Book>& books) {
	
	int countFiction = 0;
	int countNoFiction = 0;
	
	for (const Book& book : books) {
		
		switch (book.getType()) {
		case BookType::Fiction:
			++countFiction;
			break;
		case BookType::NoFiction:
			++countNoFiction;
			break;
		}
	
	}
	
	cout << "count of Fiction but with switch:" << countFiction << endl;
	cout << "count of non Fiction but wuth switch:" << countNoFiction << endl;
}


void countBooksNoSwitch(const vector <Book>& books) {
	
	int countFiction = 0;
	int countNoFiction = 0;
	
	for (const Book& book : books) {
		if (book.getType() == BookType::Fiction) {
			++countFiction;
		}
		else {
			++countNoFiction;
		}
	}
	
	cout << "count of fiction:" << countFiction << endl;
	cout << "count of non fiction:" << countNoFiction << endl;
}

int main() {
	
	Library myLibrary;
	
	myLibrary.addBook("Alexandr Pushkin", "Captain's daughter", NoFiction);
	myLibrary.addBook("Aleksey Tolstoy", "Hyperboloid of engineer Garin", NoFiction);
	myLibrary.addBook("Alexandr Pushkin", "Goldfish", Fiction);
	myLibrary.addBook("Evgeniy Shvartz", "A tale of lost time", Fiction);
	myLibrary.addBook("Sergey Lukyanenko", "Night Watch", Fiction);
	
	countBooksSwitch(myLibrary.books);
	countBooksNoSwitch(myLibrary.books);
	
	return 0;

}
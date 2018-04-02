#pragma once

#include "Book.h"
#include <vector>
#include <string>
using namespace std;

class BookRepo {
	vector<Book> list;
	bool exist(const Book& book);
public:
	BookRepo() = default;

	//nu permitem copierea de obiecte
	BookRepo(const BookRepo& ot) = delete;

	/*
	Salvare carte
	Arunca exceptie daca mai exista o carte cu acelasi nume

	*/
	virtual void store(const Book& book);


	/*
	Modify a book
	*/
	virtual void modify(const Book& book);
	/*
	Cauta o carte si o returneaza
	Arunca o exceptie daca nu exista cartea

	*/

	const Book& findByTitle(const string& title) ;

	/*
	Returneaza toate cartile salvate
	*/

	const vector<Book>& getAll();

	virtual void deleteBook(const string& title);
	
	
	class SHOP {
		vector <Book> listShop;
		bool existShop(const string& title);
	public:
		SHOP() = default;
		// don't allow to copy the objects
		SHOP(const SHOP& ot) = delete;

		/*
		Save a book
		Throw exception if there is another book whith the same title
		*/
		void storeShop(const Book& book) ;


		/*
		Delete all books
		*/
		void deleteBookShop();

		/*
		Return all the books saved
		*/
		const vector <Book>& getAllShop();

		/*
		Generate a shop with books
		*/
		void generateShop(const vector<Book>& list, int number);

		const bool findByTitleShop(const string& title);
	} MyShop;

	

};

class BookRepoFile : public BookRepo {
	string fileName;
	void loadFromFile();
	void writeToFile();
public:
	BookRepoFile(const string& _fileName) :BookRepo(), fileName(_fileName) {
		loadFromFile();
	}
	void store(const Book& book) override {
		BookRepo::store(book);
		writeToFile();
	}
	void deleteBook(const string& title) override {
		BookRepo::deleteBook(title);
		writeToFile();
	}
	
};


class BookRepoException {
	string message;

public:
	BookRepoException(string _message) : message{ _message } {};
	friend ostream& operator<<(ostream& out, const BookRepoException& exception);
	string getMessage() const {
		return message;
	};
};

class SHOPException {
	string messageShop;
public:
	SHOPException(string _messageShop) : messageShop{ _messageShop } {};
	friend ostream& operator<<(ostream& out, const SHOPException& exception);
};
void testFileRepository();
void testRepository();

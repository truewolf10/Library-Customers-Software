#pragma once

#include "Book.h"
#include "BookRepository.h"
#include <string>
#include <vector>
#include <functional>
#include "Validator.h"
#include "Export.h"
#include <memory>
#include "Undo.h"
using namespace std;

class BookStore {
	BookRepo& rep;
	BookValidator& val;
	vector < unique_ptr<UndoAction>> undoActions;
	/*


	*/
	vector<Book> generalSort(bool(*lessThan)(const Book&, const Book&));

	/*


	*/
	vector <Book> generalFilter(function<bool(const Book&)> function);
public:
	BookStore(BookRepo& _rep, BookValidator& _val) : rep{ _rep }, val{ _val } {};
	//Nu permitem copierea de obiecte in PetStore
	BookStore(const BookStore& ot) = delete;
	void operator=(const BookStore& ot) = delete;
	/*
	Return all books
	*/
	const vector<Book>& getAll() {
		return rep.getAll();
	}
	/*
	Add a new book
	Throw exception if can't save or it's invalid.
	*/
	void undo();

	void addBook(const string& title, const string& author, const string& species, int age);
	/*
	Delete a book with a title.
	*/
	void delBook(const string& title);
	/*
	Find a book
	Throw a message if he doesn't exist.
	*/
	const Book& findABook(const string & title);
	/*
	Modify a book
	*/
	void modifyBook(const string& title, const string& author, const string& species, int age);
	/*
	Return a list of books sorted by title.
	*/
	vector <Book>  sortByTitle();
	/*
	Return a list of books sorted by author.
	*/
	vector <Book> sortByAuthor();
	/*
	Return a list of books sorted by species+age.
	*/
	vector <Book> sortBySpeciesAndAge();

	vector<Book> filterByAge(int age);

	vector<Book> filterBySpecies(const string& species);
	
	vector<Book>getAllShops();
	/*
	Add a new movie by title
	Throw exception if the book can't be saved or it's invalid
	*/
	void addBookSHOP(const string& title);
	/*
	Delete all books.
	*/
	void delBookShop();
	/*
	Generate a random shop
	*/
	void generate(const vector<Book>& list, int number);
	
	/*
	Export in file CVS the SHOP
	*/
	void exportShopToCVS(const string& fileName);
	/*
	Export in file HTML the SHOP
	*/
	void exportShopToHTML(const string& fileName);
};

void testController();
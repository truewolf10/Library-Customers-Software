#pragma once

#include "BookController.h"
#include "Book.h"


class ConsoleUI {
	BookStore& ctr;

	
	/*
	Read a book to the keyboard and add it in list.
	Throw exception if he can't save or it's not valid.
	*/
	void adaugaUI();

	/*
	Print a list with all books.
	*/
	void printList(const vector<Book>& list);
	/*
	Delete a book.
	*/
	void deleteUI();
	/*
	Find a book.
	*/
	void findUI();
	
	/*
	Add to shop
	*/
	void addShopUI();
	
	/*
	Delete all book from shop
	*/
	void deleteShopUI();
	
	/*
	Generate a shop
	*/
	void generateUI();

	void addSome();
	
	void UndoUI();
	
	vector<Book> filterBySpeciesUI();
	vector <Book> filterByAgeUI();

public:
	ConsoleUI(BookStore& _ctr) : ctr{ _ctr } {}
	ConsoleUI(const ConsoleUI& ot) = delete;

	void start();


};
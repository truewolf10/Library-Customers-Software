#pragma once
#include "Book.h"
#include "BookRepository.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};

};

class UndoAdd :public UndoAction {
	Book addedBook;
	BookRepo& rep;
public:
	UndoAdd(BookRepo& _rep, const Book& _addedBook) :rep{ _rep }, addedBook{ _addedBook } { };
	void doUndo() override {
		rep.deleteBook(addedBook.getTitle());
	}
};

class UndoDelete : public UndoAction {
	Book delBook;
	BookRepo& rep;
public:
	UndoDelete(BookRepo& _rep, const Book& _delbook) :rep{ _rep }, delBook{ _delbook } {};
	void doUndo() override {
		rep.store(delBook);
	}
};
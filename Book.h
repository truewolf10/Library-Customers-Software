#pragma once


#include <string>
#include <iostream>
using namespace std;

class BookException {
	std::string message;
public:
	BookException(const string& _message) : message{ _message } {};
	string getMessage()const { return message; }
};

class Book {
	std::string title;
	std::string author;
	std::string species;
	int age;
public:
	Book(const string _title, const string _author, const string _species, int _age) :title{ _title }, author{ _author }, species{ _species }, age{ _age } {}

	Book(const Book& ot) :title{ ot.title }, author{ ot.author }, species{ ot.species }, age{ ot.age } {
	}

	string getTitle() const {
		return title;
	}
	string getAuthor() const {
		return author;
	}
	string getSpecies() const {
		return species;
	}
	int getAge() const {
		return age;
	}
	bool operator==(Book other) const
	{
		if (this->title == other.title) return true;
		else return false;
	}
};
/*
Compare by title
Return true if title of book1 less than title of book2
*/
bool cmpTitle(const Book& book1, const Book& book2);
/*
Compare by species
Return true if species of book1 less than species of book2.
*/
bool cmpSpecies(const Book& book1, const Book& book2);
/*
*/
bool cmpAuthor(const Book& book1, const Book& book2);
/*
*/
bool cmpAge(const Book& book1, const Book& book2);
/*
*/

void testBook();

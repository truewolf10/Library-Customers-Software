#include "BookRepository.h"
#include <string>
#include <assert.h>
#include <sstream>
#include <fstream> 
#include <random>
#include <chrono>
#include <algorithm>
//BOOK REPOSITORY:

void BookRepo::store(const Book& book) {
	if (exist(book)) {
		throw BookRepoException("This book already exist:" + book.getTitle() + " with author " + book.getAuthor());
	}
	list.push_back(book);
}

void BookRepo::modify(const Book & book)
{
		auto bookexist = findByTitle(book.getTitle());
		deleteBook(book.getTitle());
		store(book);
	
}


bool BookRepo::exist(const Book& book) {
	try {
		findByTitle(book.getTitle());
		return true;
	}
	catch (BookRepoException&) {
		return false;
	}
}

const Book& BookRepo::findByTitle(const string& title) {
	for (const auto& book : list) {
		if (book.getTitle() == title) {
			return book;
		}
	}
	throw BookRepoException("This book with title " + title + " doesn't exist");
}

const vector<Book>& BookRepo::getAll() {
	return list;
}

void BookRepo::deleteBook(const string& title)
{
	int i = 0, exist = 0;
	while (i < list.size()) {
		if (list[i].getTitle() == title)
		{
			list.erase(list.begin() + i);
			exist = 1;
		}
		else i++;
	}
	if (exist == 0) throw BookRepoException("This book with title " + title + " doesn't exist..\n");

}

//BOOK FILE REPOSITORY:

void BookRepoFile::loadFromFile()
{

	string title, author, species;
	int age;
	ifstream in(fileName);
	if (!in.is_open()) {
		throw BookRepoException("Unable to open file " + fileName);
	}
	while (!in.eof()) {
		in >> title;
		in >> author;
		in >> species;
		in >> age;
		if (in.eof()) break;
		Book book{ title.c_str(),author.c_str(),species.c_str(),age };
		BookRepo::store(book);
	}
	in.close();
}

void BookRepoFile::writeToFile()
{
	ofstream out(fileName);
	if (!out.is_open()) {
		throw BookRepoException("Unable to open file " + fileName);
	}
	for (const auto& book : getAll()) {
		out << book.getTitle() << endl;
		out << book.getAuthor() << endl;
		out << book.getSpecies() << endl;
		out << book.getAge() << endl;
	}
	out.close();
}


bool BookRepo::SHOP::existShop(const string & title)
{
	for (const auto& book : listShop) {
		if (book.getTitle() == title)
			return true;
	}
	return false;
}

void BookRepo::SHOP::storeShop(const Book & book)
{
	if (existShop(book.getTitle())) {
		throw SHOPException("This book already exists: " + book.getTitle() + "\n");

	}
	listShop.push_back(book);
}

void BookRepo::SHOP::deleteBookShop()
{
	listShop.clear();
}

const vector<Book>& BookRepo::SHOP::getAllShop()
{
	return listShop;
}

void BookRepo::SHOP::generateShop(const vector<Book>& list, int number)
{
	vector<Book> random = list;
	std::shuffle(random.begin(), random.end(), std::default_random_engine(std::random_device{}()));
	while (listShop.size() < number&& random.size() > 0) {
		if (!findByTitleShop(random.back().getTitle())) {
			listShop.push_back(random.back());
		}
		random.pop_back();
	}
	if (listShop.size() < number) throw SHOPException("Can't generate the shop you want, but I add some books..");
}

const bool BookRepo::SHOP::findByTitleShop(const string & title)
{
	for (const auto& book : listShop) {
		if (book.getTitle() == title)
			return true;
	}
	return false;
}


ostream & operator<<(ostream & out, const SHOPException & exception)
{
	out << exception.messageShop;
	return out;
}


ostream& operator <<(ostream& out, const BookRepoException& exception) {
	out << exception.message;
	return out;
}


void testOperatorBookShopException() {
	SHOPException message("Message");
	ostringstream out;
	out << message;
	assert(out.str() == "Message");

}
void testAddShop() {
	BookRepo::SHOP repShop;
	Book book1{ "title1","author1","species1",2000 };
	Book book2{ "title2","author2","species2",2001 };
	Book book3{ "title3","author3","species3",2002 };
	repShop.storeShop(book1);
	repShop.storeShop(book2);
	assert(repShop.getAllShop().size() == 2);
	repShop.storeShop(book3);
	assert(repShop.getAllShop().size() == 3);
	try {
		repShop.storeShop(book1); assert(false);}
	catch (SHOPException&) {
		assert(true);
	}

}

void testRepositoryShop()
{
	testAddShop();
	testOperatorBookShopException();
}


void testAdd() {
	BookRepo rep;
	rep.store(Book{ "title1","author1","species1",2000 });
	assert(rep.getAll().size() == 1);
	assert(rep.findByTitle("title1").getSpecies() == "species1");
	assert(rep.findByTitle("title1").getAge() == 2000);


	rep.store(Book{ "title2","author2","species2",2001 });
	assert(rep.getAll().size() == 2);


	try {
		rep.store(Book{ "title2","author2","species2",2001 });assert(false);}
	catch (BookRepoException&) {
		assert(true);}
}
void testFind() {
	BookRepo rep;
	rep.store(Book{ "title1","author1","species1",2000 });
	rep.store(Book{ "title2","author2","species2",2001 });

	auto book = rep.findByTitle("title2");
	assert(book.getAge() == 2001);
	assert(book.getAuthor() == "author2");
	try
	{
		rep.findByTitle("None");assert(false);}
	catch (BookRepoException&) {
		assert(true);}
}
void testDelete() {
	BookRepo rep;
	rep.store(Book{ "title1","author1","species1",2000 });
	rep.store(Book{ "title2","author2","species2",2001 });

	assert(rep.getAll().size() == 2);
	rep.deleteBook("title1");
	assert(rep.getAll().size() == 1);

	try {
		rep.deleteBook("None");assert(false);}
	catch (BookRepoException&) {
		assert(true);}
}
void testOperatorBookException() {
	BookRepoException message("Message");
	ostringstream out;
	out << message;
	assert(out.str() == "Message");

}

void testFileRepository()
{
	ofstream out("BookTest.txt", ios::trunc);
	out.close();
	BookRepoFile repFile{ "BookTest.txt" };
	repFile.store(Book{ "title1","author1","species1",1990 });

	BookRepoFile repFileLoaded{ "BookTest.txt" };
	auto book = repFileLoaded.findByTitle("title1");
	assert(book.getAge() == 1990);
	try {
		repFileLoaded.findByTitle("title2");
		assert(false);
	}
	catch (BookRepoException&) {};
	repFileLoaded.deleteBook("title1");
	assert(repFileLoaded.getAll().size() == 0);
	try {
		repFileLoaded.deleteBook("title1");
		assert(false);}
	catch (BookRepoException&) {};
	BookRepoException repFileLoaded2{ "BookTest.txt" };

}
void testRepository() {
	testRepositoryShop();
	testFileRepository();
	testFind();
	testAdd();
	testDelete();
	testOperatorBookException();

}


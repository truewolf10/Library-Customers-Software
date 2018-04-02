#include "BookController.h"
#include <functional>
#include <assert.h>
#include <algorithm>
using namespace std;

vector <Book> BookStore::generalSort(bool(*lessThan)(const Book&, const Book&)) {
	vector <Book> listSec{ rep.getAll() };
	for (size_t i = 0; i < listSec.size(); i++) {
		for (size_t j = i + 1; j < listSec.size(); j++) {
			if (!lessThan(listSec[i], listSec[j])) {
				Book aux = listSec[i];
				listSec[i] = listSec[j];
				listSec[j] = aux;

			}
		}
	}
	return listSec;
}

vector<Book> BookStore::generalFilter(function<bool(const Book&)> function)
{
	vector <Book> listaSec{ rep.getAll() }, listaRez;
	for (size_t i = 0; i < listaSec.size(); i++)
		if (function(listaSec[i]))
			listaRez.push_back(listaSec[i]);
	return listaRez;

}

void BookStore::undo()
{
	if (undoActions.empty()) {
		throw BookRepoException("We don't have another operations.");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void BookStore::addBook(const string & title, const string & author, const string & species, int age) {
	Book book{ title,author,species,age };
	val.Validate(book);
	rep.store(book);
	undoActions.push_back(make_unique<UndoAdd>(rep, book));
}

void BookStore::delBook(const string & title)
{
	undoActions.push_back(make_unique<UndoDelete>(rep, findABook(title)));
	rep.deleteBook(title);
	
}




const Book & BookStore::findABook(const string & title)
{
	return rep.findByTitle(title);
}

void BookStore::modifyBook(const string & title, const string & author, const string & species, int age)
{
	Book book{ title,author,species,age };
	rep.modify(book);
}

vector<Book> BookStore::sortByTitle()
{
	return generalSort(cmpTitle);
}

vector<Book> BookStore::sortByAuthor()
{
	return generalSort(cmpAuthor);
}

vector<Book> BookStore::sortBySpeciesAndAge()
{
	/*return generalSort([](const Book& book1, const Book& book2) {
		if (book1.getSpecies() == book2.getSpecies()) {
		return book1.getAge() < book2.getAge();
		}
		return book1.getSpecies() < book2.getSpecies();
	});
	*/
	auto rez = getAll();
	sort(rez.begin(),rez.end(),[](const Book& book1, const Book& book2) {
		if (book1.getSpecies() == book2.getSpecies()) {
			return book1.getAge() < book2.getAge();
		}
		return book1.getSpecies() < book2.getSpecies();
	});
	return rez;
}

vector<Book> BookStore::filterByAge(int age)
{
	return generalFilter([age](const Book& book) {
		return book.getAge() > age;
	});
}

vector<Book> BookStore::filterBySpecies(const string& species)
{
	string specie = species;
	return generalFilter([specie](const Book& book) {return book.getSpecies() == specie; });
}

vector<Book> BookStore::getAllShops()
{
	return rep.MyShop.getAllShop();
}

void BookStore::addBookSHOP(const string & title)
{
	rep.MyShop.storeShop(rep.findByTitle(title));
}

void BookStore::delBookShop()
{
	rep.MyShop.deleteBookShop();
}

void BookStore::generate(const vector<Book>& list, int number)
{
	rep.MyShop.generateShop(list, number);
}

void BookStore::exportShopToCVS(const string & fileName)
{
	exportToCVS(fileName, getAllShops());
}

void BookStore::exportShopToHTML(const string & fileName)
{
	exportToHTML(fileName, getAllShops());
}



void testAddBook() {
	BookRepo rep;
	BookValidator val;
	BookStore ctr{ rep,val };
	ctr.addBook("title1", "author1", "species1", 2000);
	assert(ctr.getAll().size() == 1);
	try {
		ctr.addBook("", "author", "", -1);
		assert(false);}
	catch (ValidateException&) {
		assert(true);}
	try {
		ctr.addBook("title1", "author1", "species1", 2000);
		assert(false);}
	catch (ValidateException&) {
		assert(true);}
	catch (BookRepoException&) {
		assert(true);}
	
}
void testDelBook() {
	BookRepo rep;
	BookValidator val;
	BookStore ctr{ rep,val };
	ctr.addBook("title1", "author1", "species1", 2000);
	assert(ctr.getAll().size() == 1);
	ctr.delBook("title1");
	assert(ctr.getAll().size() == 0);

}

void testSort() {
	BookRepo rep;
	BookValidator val;
	BookStore ctr{ rep,val };
	ctr.addBook("title1", "author4", "species3", 2000);
	ctr.addBook("title4", "author1", "species2", 2001);
	ctr.addBook("title2", "author2", "species1", 2004);
	ctr.addBook("title3", "author3", "species1", 2003);

	auto firstBook = ctr.sortByTitle()[0];
	assert(firstBook.getTitle() == "title1");
	assert(firstBook.getAuthor() == "author4");

	firstBook = ctr.sortBySpeciesAndAge()[0];
	assert(firstBook.getAge() == 2003);
	assert(firstBook.getSpecies() == "species1");

	firstBook = ctr.sortByAuthor()[0];
	assert(firstBook.getAuthor() == "author1");


}
void testFilter() {
	BookRepo rep;
	BookValidator val;
	BookStore ctr{ rep,val };
	ctr.addBook("title1", "author4", "species3", 500);
	ctr.addBook("title4", "author1", "species2", 1001);
	ctr.addBook("title2", "author2", "species1", 4004);
	ctr.addBook("title3", "author3", "species1", 3003);
	assert(ctr.filterByAge(2000).size() == 2);
	assert(ctr.filterByAge(5000).size() == 0);
	assert(ctr.filterByAge(0).size() == 4);
	assert(ctr.filterBySpecies("species1").size() == 2);
	assert(ctr.filterBySpecies("None").size() == 0);

}
void testController()
{
	testFilter();
	testSort();
	testDelBook();
	testAddBook();
}

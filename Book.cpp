#include "Book.h"
#include <assert.h>

bool cmpTitle(const Book & book1, const Book & book2)
{
	return book1.getTitle() < book2.getTitle();
}

bool cmpSpecies(const Book & book1, const Book & book2)
{
	return book1.getSpecies() < book2.getSpecies();

}

bool cmpAuthor(const Book & book1, const Book & book2)
{
	return book1.getAuthor() < book2.getAuthor();

}

bool cmpAge(const Book & book1, const Book & book2)
{
	return book1.getAge() < book2.getAge();
}



void testBook()
{
	Book book{ "Ion","Rebreanu","Epic",1960 };
	assert(book.getAge() == 1960);
	assert(book.getAuthor() == "Rebreanu");
	assert(book.getTitle() == "Ion");
	assert(book.getSpecies() == "Epic");
	Book book2{ "Ion","Rebreanu","Epic",1960 };
	assert(book == book2);
	Book book3{ "Poezii","Eminescu","Liric",1859 };
	assert(!(book3 == book2));
	assert(cmpAge(book2, book3) == false);
	assert(cmpTitle(book, book3) == true);
	assert(cmpSpecies(book3, book) == false);
	assert(cmpAuthor(book2, book3) == false);
}

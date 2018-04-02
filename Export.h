#pragma	once
#include <string>
#include <vector>
#include "Book.h"

/*
Write in file fileName the list of books in format Comma Values Separated
Throw BookException if it can't create the file.
*/
void exportToCVS(const std::string& fileName, const std::vector<Book>& books);

/*
Write in file fileName the list of books in format HTML
Throw BookException if can't create the file
*/
void exportToHTML(const std::string& fileName, const std::vector<Book>& books);


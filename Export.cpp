#include "Export.h"
#include "Book.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void exportToCVS(const std::string & fileName, const std::vector<Book>& books)
{
	ofstream out(fileName, ios::trunc);
	if (!out.is_open()) {
		throw BookException("Unable to open file:" + fileName);
	}
	for (const auto& book : books) {
		out << book.getTitle() << ",";
		out << book.getAuthor() << ",";
		out << book.getSpecies() << ",";
		out << book.getAge() << ",";

	}
	out.close();


}

void exportToHTML(const std::string & fileName, const std::vector<Book>& books)
{
	ofstream out(fileName, ios::trunc);
	if (!out.is_open()) {
		throw BookException("Unable to open file:" + fileName);
	}
	out << "<html><body>" << endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << endl;
	for (const auto& book : books) {
		out << "<tr>" << book.getTitle() << "</tr>" << endl;
		out << "<tr>" << book.getAuthor() << "</tr>" << endl;
		out << "<tr>" << book.getSpecies() << "</tr>" << endl;
		out << "<tr>" << book.getAge() << "</tr>" << endl;

	}
	out << "</table>" << endl;
	out << "</body></html>" << endl;
	out.close();
}

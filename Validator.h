#pragma once


#include <string>
#include "Book.h"
#include <vector>
using namespace std;

class ValidateException {
	vector <string> messages;
public:
	ValidateException(const vector<string>& errors) : messages{ errors } {}
	friend ostream& operator<<(ostream& out, const ValidateException& exception);
	const string getMessage() {
		string rez;
		for (auto msg : messages) {
		rez += msg;
		rez += "\n";
		}
		return rez;
	}
};

ostream & operator<<(ostream & out, const ValidateException & exception);

class BookValidator {
public:
	void Validate(const Book& book);
};
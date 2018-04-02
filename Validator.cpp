#include "Validator.h"


void BookValidator::Validate(const Book& book) {
	vector <string> messages;
	if (book.getAuthor().size() == 0) messages.push_back("Incorrect author! Try again..");
	if (book.getSpecies().size() == 0) messages.push_back("Incorrect species! Try again..");
	if (book.getTitle().size() == 0) messages.push_back("Incorrect title! Try again..");
	if (book.getAge() < 0) messages.push_back("Negative age ! Try again..");
	if (messages.size() > 0) {
		throw ValidateException(messages);
	}

}




ostream & operator<<(ostream & out, const ValidateException & exception)
{
	for (const auto& message : exception.messages) {
		out << message << " ";
	}
	return out;
}

#include "BookConsole.h"
#include "Book.h"
#include <iostream>
#include <string>

using namespace std;

template<typename Type>
Type MyRead(const char* msg) {
	Type command;
	while (true) {
		cout << endl << msg;
		cin >> command;
		bool fail = cin.fail();
		cin.clear();
		auto& aux = cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1) {
			break;
		}
	}
	return command;
}

void ConsoleUI::printList(const vector<Book>& list) {
	cout << "TITLE  AUTHOR   SPECIES   AGE \n";
	for (const auto& book : list) {
		cout << ' ' << book.getTitle() << ' ' << book.getAuthor() << ' ' << book.getSpecies() << ' ' << book.getAge() << '\n';
	}
	cout << '\n';

}

void ConsoleUI::deleteUI()
{
	string title;
	cout << "Insert title"; cin >> title;
	ctr.delBook(title);
	cout <<"Delete succesfully..\n";

}

void ConsoleUI::findUI()
{
	string title;
	cout << "Insert title:";
	cin >> title;
	Book book = ctr.findABook(title);
	cout << "TITLE  AUTHOR   SPECIES   AGE \n";
	cout << book.getTitle() << " " << book.getAuthor() << " " << book.getSpecies() << " " << book.getAge()<< "\n";




}

void ConsoleUI::addShopUI()
{
	string title;
	cout << "Insert title:";
	cin >> title;
	ctr.addBookSHOP(title);
	cout << "Book succesfully added.."<<endl;
	

}

void ConsoleUI::deleteShopUI()
{
	ctr.delBookShop();
	cout << "Shop succesfully clean.."<<endl;

}

void ConsoleUI::generateUI()
{
	int number = MyRead<int>("Insert number of books you want:");
	ctr.generate(ctr.getAll(), number);
	cout << "Generate succesfully.." << endl;;
}


void ConsoleUI::addSome()
{
	ctr.addBook("Ion", "Rebreanu", "Epic", 1950);
	ctr.addBook("Poezii", "Eminescu", "Liric", 1870);
}

void ConsoleUI::UndoUI()
{
	ctr.undo();
	cout << "Undo succesfully.." << endl;
	printList(ctr.getAll());
}

vector<Book> ConsoleUI::filterBySpeciesUI()
{
	string species;
	cout << "Insert species:";
	cin >> species;
	return ctr.filterBySpecies(species);
}

vector<Book> ConsoleUI::filterByAgeUI()
{
	int age;
	cout << "insert age:";
	cin >> age;
	return ctr.filterByAge(age);
}

void ConsoleUI::adaugaUI() {
	string title, author, species;
	int age;
	cout << "Insert title:";
	cin >> title;
	cout << "Insert author:";
	cin >> author;
	cout << "Insert species:";
	cin >> species;
	cout << "Insert age:";
	cin >> age;
	ctr.addBook(title, author, species, age);
	cout << "Add succesfully..\n";


}

void ConsoleUI::start() {
	addSome();
	while (true) {
		cout << "MENU:\n";
		cout << "1.Add a book.\n2.Print list.\n3.Delete a book.\n4.Find by title.\n5.Sort by author.\n6.Sort by title.\n7.Sort by species+age.\n8.Filter by age.\n9.Filter by species\n10.Add to shop.\n11.Delete shop.\n12.Generate books in shop.\n13.Print shop.\n14.Undo.\n0.EXIT\n";
		int cmd;
		cmd=MyRead<int>("Insert command:");
		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				printList(ctr.getAll());
				break;
			case 3:
				deleteUI();
				break;
			case 4:
				findUI();
				break;
			case 5:
				printList(ctr.sortByAuthor());
				break;
			case 6:
				printList(ctr.sortByTitle());
				break;
			case 7:
				printList(ctr.sortBySpeciesAndAge());
				break;
			case 8:
				printList(filterByAgeUI());	
				break;
			case 9:
				printList(filterBySpeciesUI());
				break;
			case 10:
				addShopUI();
				break;
			case 11:
				deleteShopUI();
				break;
			case 12:
				generateUI();
				break;
			case 13:
				printList(ctr.getAllShops());
				break;
			case 14:
				UndoUI();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida\n";
			}

		}
		catch (BookRepoException& ex) {
			cout << ex << '\n';
		}
		catch (ValidateException& ex) {
			cout << ex << '\n';
		}
		catch (SHOPException& ex) {
			cout << ex << "\n";
		}
	}
}
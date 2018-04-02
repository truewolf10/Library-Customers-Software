#include "bibliotecacartigui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qlist.h>

#include "Book.h"
#include "BookRepository.h"
#include "BookController.h"
#include "Validator.h"

void testAll() {
	testBook();
	testRepository();
	testController();
}
int main(int argc, char *argv[])
{
	testAll();
	BookRepoFile rep("Carti.txt");
	BookValidator val;
	BookStore ctr{rep,val};	
	QApplication a(argc, argv);
	BibliotecaCartiGUI GUI{ ctr };
	GUI.show();
	a.exec();
	return 0;
}

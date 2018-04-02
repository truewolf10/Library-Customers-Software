#ifndef BIBLIOTECACARTIGUI_H
#define BIBLIOTECACARTIGUI_H

#include <QtWidgets/QMainWindow>
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include "BookController.h"
#include "Book.h"
#include <vector>
#include <qlabel.h>

class BibliotecaCartiGUI : public QWidget{
private:
	BookStore& ctr;
	QListWidget* list;
	QLineEdit* textTitle;
	QLineEdit* textAuthor;
	QLineEdit* textSpecies;
	QLineEdit* textAge;
	QPushButton* buttonAdd;
	QPushButton* buttonDel;
	QPushButton* buttonModify;
	QPushButton* buttonFindT;
	QPushButton* buttonUndo;
	QPushButton* buttonSortByTitle;
	QPushButton* buttonSortBySpAg;
	QPushButton* buttonSortByAuthor;
	QPushButton* buttonFilterByAge;
	QPushButton* buttonFilterBySpecies;
	QLineEdit* textFilter;
	void initGUICmps();
	void connectSignalsSlots();
	void addBookGUI();
	void delBookGUI();
	void UndoGUI();
	void filterByAgeGUI();
	void filterBySpeciesGUI();
	void modifyBookGUI();

	void reloadList(const std::vector<Book>& books);
public:
	BibliotecaCartiGUI(BookStore& _ctr) : ctr{ _ctr } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(ctr.getAll());
	}
};

#endif // BIBLIOTECACARTIGUI_H

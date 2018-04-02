#include "bibliotecacartigui.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <algorithm>
#include <QtWidgets>
#include "Book.h"
#include <vector>
#include <iterator>

void BibliotecaCartiGUI::initGUICmps()
{
	QHBoxLayout* layout = new QHBoxLayout;
	setLayout(layout);

	QWidget* widgetRight = new QWidget;
	QVBoxLayout* vertLayout = new QVBoxLayout;
	widgetRight->setLayout(vertLayout);
	list = new QListWidget;
	vertLayout->addWidget(list);

	
	QWidget* widgetButtonR = new QWidget;
	QHBoxLayout* layoutButtonR = new QHBoxLayout;
	widgetButtonR->setLayout(layoutButtonR);
	
	buttonSortByTitle = new QPushButton("Sort by Title");
	layoutButtonR->addWidget(buttonSortByTitle);
	
	buttonSortBySpAg = new QPushButton("Sort by Species&Age");
	layoutButtonR->addWidget(buttonSortBySpAg);
	
	buttonSortByAuthor = new QPushButton("Sort by Author");
	layoutButtonR->addWidget(buttonSortByAuthor);
	vertLayout->addWidget(widgetButtonR);

	QWidget* filterWidget = new QWidget;
	QHBoxLayout* filterLine = new QHBoxLayout;
	filterWidget->setLayout(filterLine);
	textFilter = new QLineEdit;
	buttonFilterByAge = new QPushButton("Filter by age");
	buttonFilterBySpecies = new QPushButton("Filter by species");
	filterLine->addWidget(buttonFilterByAge);
	filterLine->addWidget(buttonFilterBySpecies);
	filterLine->addWidget(textFilter);

	vertLayout->addWidget(filterWidget);
	layout->addWidget(widgetRight);


	QWidget* widgetDetails = new QWidget;
	QFormLayout* formDetails = new QFormLayout;
	widgetDetails->setLayout(formDetails);
	textTitle = new QLineEdit;
	formDetails->addRow(new QLabel("Title:"), textTitle);
	textAuthor = new QLineEdit;
	formDetails->addRow(new QLabel("Author:"), textAuthor);
	textSpecies = new QLineEdit;
	formDetails->addRow(new QLabel("Species:"), textSpecies);
	textAge = new QLineEdit;
	formDetails->addRow(new QLabel("Age:"), textAge);
	QWidget* bookButtons = new QWidget;
	QHBoxLayout* allB = new QHBoxLayout;
	buttonAdd = new QPushButton("ADD Book");
	allB->addWidget(buttonAdd);
	
	buttonDel = new QPushButton("Delete Book");
	allB->addWidget(buttonDel);
	
	buttonModify = new QPushButton("Modify a book");
	allB->addWidget(buttonModify);
	
	buttonUndo = new QPushButton("UNDO");
	allB->addWidget(buttonUndo);
	

	
	
	bookButtons->setLayout(allB);
	
	
	
	
	
	
	
	formDetails->addWidget(bookButtons);

	layout->addWidget(widgetDetails);
}

void BibliotecaCartiGUI::connectSignalsSlots(){
	QObject::connect(buttonSortByTitle, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByTitle());
	});
	QObject::connect(buttonSortByAuthor, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByAuthor());
	});
	QObject::connect(buttonSortBySpAg, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortBySpeciesAndAge());
	});
	QObject::connect(list, &QListWidget::itemSelectionChanged, [&](){
		if (!list->selectedItems().isEmpty()) {
			QListWidgetItem* selectItem = list->selectedItems().at(0);
			QString title = selectItem->text();
			textTitle->setText(title);
			try {
				Book book = ctr.findABook(title.toStdString());
				textAuthor->setText(QString::fromStdString(book.getAuthor()));
				textSpecies->setText(QString::fromStdString(book.getSpecies()));
				textAge->setText(QString::number(book.getAge()));

			}
			catch (BookRepoException& ex) {
				QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMessage()));

			}
		}
		else {
			textTitle->setText("");
			textSpecies->setText("");
			textAuthor->setText("");
			textAge->setText("");

		}

	});
	
	QObject::connect(buttonAdd, &QPushButton::clicked, this, &BibliotecaCartiGUI::addBookGUI);
	QObject::connect(buttonDel, &QPushButton::clicked, this, &BibliotecaCartiGUI::delBookGUI);
	QObject::connect(buttonUndo, &QPushButton::clicked, this, &BibliotecaCartiGUI::UndoGUI);
	QObject::connect(buttonModify, &QPushButton::clicked, this, &BibliotecaCartiGUI::modifyBookGUI);
	QObject::connect(buttonFilterBySpecies, &QPushButton::clicked, this, &BibliotecaCartiGUI::filterBySpeciesGUI);
	QObject::connect(buttonFilterByAge, &QPushButton::clicked, this, &BibliotecaCartiGUI::filterByAgeGUI);
}

void BibliotecaCartiGUI::addBookGUI()
{
	try {
		ctr.addBook(textTitle->text().toStdString(), textAuthor->text().toStdString(), textSpecies->text().toStdString(), textAge->text().toDouble());
			reloadList(ctr.getAll());
	}
	catch (BookRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMessage()));

	}
	catch (ValidateException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMessage()));

	}
	
}

void BibliotecaCartiGUI::delBookGUI()
{
	try {
		auto title = textTitle->text().toStdString();
		ctr.delBook(title);
		reloadList(ctr.getAll());

	}
	catch (BookRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMessage()));

	}

}

void BibliotecaCartiGUI::UndoGUI()
{
	try {
		ctr.undo();
		reloadList(ctr.getAll());
		QMessageBox::information(nullptr, "Succes", QString::fromStdString("Succesfully undo!"));

	}
	catch (BookRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMessage()));

	}
}

void BibliotecaCartiGUI::filterByAgeGUI(){
	bool ok;
	int age = textFilter->text().toInt(&ok, 10);
	if (ok) {
		auto colorize = ctr.filterByAge(age);
		list->clear();
		auto all = ctr.getAll();
		for (auto book : all) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.getTitle()), list);
			if (std::find(colorize.begin(), colorize.end(), book) != colorize.end()) {
				item->setBackgroundColor(QColor(Qt::green));
			}
		}

	}
	else
		QMessageBox::warning(nullptr,"Warning",QString::fromStdString("Insert a number !"));

}

void BibliotecaCartiGUI::filterBySpeciesGUI(){
	string species = textFilter->text().toStdString();
	auto colorize = ctr.filterBySpecies(species);
	list->clear();
	auto all = ctr.getAll();
	for (const auto book :all ) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.getTitle()), list);
		if (std::find(colorize.cbegin(), colorize.cend(), book) != colorize.end()) {
			item->setBackgroundColor(QColor(Qt::green));
		}
	}
}

void BibliotecaCartiGUI::modifyBookGUI()
{
	try {
		ctr.modifyBook(textTitle->text().toStdString(), textAuthor->text().toStdString(), textSpecies->text().toStdString(), textAge->text().toDouble());
		reloadList(ctr.getAll());
		QMessageBox::information(nullptr, "Succes", QString::fromStdString("Book modified succesfully!"));
	}
	catch (BookRepoException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMessage()));

	}
	catch (ValidateException& ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMessage()));

	}
}






void BibliotecaCartiGUI::reloadList(const std::vector<Book>& books)
{

	list->clear();
	for (const auto& book : books) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.getTitle()), list);
	}
}

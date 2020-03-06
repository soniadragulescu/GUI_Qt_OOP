#include "GUI.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

void GUI::initGUIcomponents() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub, butoanele
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);

	//list = new QListWidget;
	list = new QListView;
	vl->addWidget(list);

	QWidget* butoaneDreapta = new QWidget;
	QHBoxLayout* lyButoaneDreapta = new QHBoxLayout;
	butoaneDreapta->setLayout(lyButoaneDreapta);
	//buton sorteaza dupa pret
	butonSortByPrice = new QPushButton("Sorteaza dupa pret");
	lyButoaneDreapta->addWidget(butonSortByPrice);

	//buton genereaza1000
	butonGenereaza1000 = new QPushButton("Genereaza100");
	lyButoaneDreapta->addWidget(butonGenereaza1000);

	vl->addWidget(butoaneDreapta);
	ly->addWidget(widDreapta);

	//detalii
	QWidget* detalii = new QWidget;
	QFormLayout* lyDetalii = new QFormLayout;
	detalii->setLayout(lyDetalii);
	textNume = new QLineEdit;
	lyDetalii->addRow(new QLabel("Nume:"), textNume);
	textTip = new QLineEdit;
	lyDetalii->addRow(new QLabel("Tip:"), textTip);
	textPret = new QLineEdit;
	lyDetalii->addRow(new QLabel("Pret:"), textPret);
	textProducator = new QLineEdit;
	lyDetalii->addRow(new QLabel("Producator:"), textProducator);

	QWidget* widStanga = new QWidget;
	QHBoxLayout* lyStanga = new QHBoxLayout;
	widStanga->setLayout(lyStanga);

	//buton adauga
	butonAdauga = new QPushButton("Adauga");
	lyStanga->addWidget(butonAdauga);
	//buton sterge
	butonSterge = new QPushButton("Sterge");
	lyStanga->addWidget(butonSterge);
	//buton update
	butonModifica = new QPushButton("Update");
	lyStanga->addWidget(butonModifica);
	// buton undo
	butonUndo = new QPushButton("Undo");
	lyStanga->addWidget(butonUndo);
	// buton cos
	butonShowCos = new QPushButton("Cos");
	lyStanga->addWidget(butonShowCos);

	vl->addWidget(widStanga);
	lyButoaneDreapta->addWidget(detalii);
}

void GUI::connectSignalsSlots() {
	//semnal clicked pt a reincarca lista ordonata dupa pret
	QObject::connect(butonSortByPrice, &QPushButton::clicked, [&]() {
		reloadList(m.sortByPrice());
	});

	//reincarca lista detalii
	QObject::connect(list->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (list->selectionModel()->selectedIndexes().isEmpty()) {
			//nu este nimic selectat (golesc detaliile)
			textNume->setText("");
			textTip->setText("");
			textPret->setText("");
			textProducator->setText("");
			return;
		}
		auto selIndex = list->selectionModel()->selectedIndexes().at(0);
		QString nume = selIndex.data(Qt::DisplayRole).toString();
		textNume->setText(nume);
		QString tip = selIndex.data(Qt::UserRole).toString();
		textTip->setText(tip);
		try {
			//cautam Produs
			Produs p = m.cautaProdus(nume.toStdString(), tip.toStdString());
			textPret->setText(QString::number(p.getPret()));
			textProducator->setText(QString::fromStdString(p.getProducator()));
		}
		catch (RepoException& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Nu exista produsul!"));
		}
	});
	/*QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
		if (list->selectedItems().isEmpty()) {
			//nu este nimic selectat
			//golesc detaliile
			textNume->setText("");
			textTip->setText("");
			textPret->setText("");
			textProducator->setText("");
			return;
		}
		QListWidgetItem* selectedItem = list->selectedItems().at(0);
		QString nume = selectedItem->text();
		textNume->setText(nume);
		QString tip = selectedItem->data(Qt::UserRole).toString();
		textTip->setText(tip);
		try {
			Produs p = m.cautaProdus(nume.toStdString(), tip.toStdString());
			textPret->setText(QString::number(p.getPret()));
			textProducator->setText(QString::fromStdString(p.getProducator()));
		}
		catch (RepoException&) {
			QMessageBox::warning(nullptr, "Warning", "Nu exista produsul!");
		}
		
	});*/

	//buton adaug
	QObject::connect(butonAdauga, &QPushButton::clicked, this, &GUI::adauga);
	//buton sterge
	QObject::connect(butonSterge, &QPushButton::clicked, this, &GUI::sterge);
	//buton update
	QObject::connect(butonModifica, &QPushButton::clicked, this,&GUI::modifica);
	//buton undo
	QObject::connect(butonUndo, &QPushButton::clicked, this, &GUI::undo);
	//buton cos
	QObject::connect(butonShowCos, &QPushButton::clicked, this, &GUI::deschideCos);

}

void GUI::adauga() {
	try {
		m.adaugaProdus(textNume->text().toStdString(), textTip->text().toStdString(), textPret->text().toDouble(), textProducator->text().toStdString());
		this->reloadList(m.getAll());
	}
	catch (RepoException&) {
		QMessageBox::warning(this, "Warning", "Exista deja produsul!");
	}
	catch (ValidatorException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString( e.getMsg()));
	}
}
void GUI::sterge() {
	try {
		m.stergeProdus(textNume->text().toStdString(), textTip->text().toStdString());
		this->reloadList(m.getAll());
	}
	catch (RepoException&) {
		QMessageBox::warning(this, "Warning", "Nu exista produsul!");
	}

}
void GUI::modifica() {
	try {
		m.modificaProdus(textNume->text().toStdString(), textTip->text().toStdString(), textPret->text().toDouble());
		this->reloadList(m.getAll());
	}
	catch (RepoException&) {
		QMessageBox::warning(this, "Warning", "Nu exista produsul!");
	}
}
void GUI::undo() {
	try {
		m.undo();
		this->reloadList(m.getAll());
	}
	catch(RepoException&) {
		QMessageBox::warning(this, "Warning", "No operations to undo!");
	}
}
void GUI::sortByPrice() {
		this->reloadList(m.sortByPrice());
}

void GUI::filtreazaPret(const double pret)
{
}

void GUI::deschideCos() {
	CosGUI* cos=new CosGUI(m.getCos());
	cos->show();
	repaint();
}

void GUI::reloadList(const vector<Produs>& products) {
	/*list->clear();
	for (const auto& p : products) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getNume()), list);
		item->setData(Qt::UserRole, QString::fromStdString(p.getTip()));

		item->setData(Qt::BackgroundRole, QBrush{ Qt::red });
	}*/
	labelCate->setText(QString{ "Cate:" }+QString::number(products.size()));
	model = new ListModel(products);
	list->setModel(model);
	//reincarca lista detalii
	QObject::connect(list->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (list->selectionModel()->selectedIndexes().isEmpty()) {
			//nu este nimic selectat (golesc detaliile)
			textNume->setText("");
			textTip->setText("");
			textPret->setText("");
			textProducator->setText("");
			return;
		}
		auto selIndex = list->selectionModel()->selectedIndexes().at(0);
		QString nume = selIndex.data(Qt::DisplayRole).toString();
		textNume->setText(nume);
		QString tip = selIndex.data(Qt::UserRole).toString();
		textTip->setText(tip);
		try {
			//cautam Produs
			Produs p = m.cautaProdus(nume.toStdString(), tip.toStdString());
			textPret->setText(QString::number(p.getPret()));
			textProducator->setText(QString::fromStdString(p.getProducator()));
		}
		catch (RepoException& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Nu exista produsul!"));
		}
	});
	/*Produs p2{ "a","a",2, "a" };
	QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p2.getNume()), list);
	item->setData(Qt::UserRole, QString::fromStdString(p2.getTip()));*/
}

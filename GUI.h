#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include "Magazin.h"
#include <qlabel.h>
#include <qdebug.h>
#include <iostream>
#include "CosGUI.h"
#include <qpainter.h>
#include "ListModel.h"

class GUI: public QWidget
{
private:
	Magazin& m;
	ListModel* model;
	QLabel* labelCate = new QLabel("Cate: 0");
	QListView* list;
	//QListWidget* list;
	QPushButton* butonAdauga;
	QPushButton* butonSterge;
	QPushButton* butonModifica;
	QPushButton* butonUndo;
	QPushButton* butonSortByPrice;
	QPushButton* butonShowCos;
	QPushButton* butonGenereaza1000;

	QLineEdit* textNume;
	QLineEdit* textTip;
	QLineEdit* textPret;
	QLineEdit* textProducator;

	void initGUIcomponents();
	void connectSignalsSlots();
	
	void adauga();
	void sterge();
	void modifica();
	void undo();
	void sortByPrice();
	void filtreazaPret(const double pret);
	void deschideCos();
	void reloadList(const vector<Produs>& products);

public:
	GUI(Magazin& m) :m{ m } {
		initGUIcomponents();
		list->setUniformItemSizes(true);
		connectSignalsSlots();
		reloadList(m.getAll());
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x, y;
		for (int i = 0; i < 40; ++i) {
			x = rand() % width();
			y = rand() % height();
			p.drawLine(0, 0, x, y);
		}
	}
	~GUI()=default;
};


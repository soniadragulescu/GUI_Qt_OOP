#pragma once
#include "CosCumparaturi.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <vector>
#include <qobject.h>
#include <qlayout.h>
using std::vector;
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlabel.h>
class CosGUI: public QWidget, public Observer
{
	CosCumparaturi& c;
	QListWidget* lst;
	QPushButton* butonAddRandom;
	QPushButton* butonClear;
	QLineEdit* numarRandom;

	void loadList(const vector<Produs>& products) {
		lst->clear();
		for (auto& p : products) {
			lst->addItem(QString::fromStdString(p.getNume()));
		}
	}

	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		lst = new QListWidget;
		ly->addWidget(lst);
		butonClear = new QPushButton{ "Goleste cos" };
		ly->addWidget(butonClear);
		QWidget* detalii = new QWidget;
		QFormLayout* lyDetalii = new QFormLayout;
		detalii->setLayout(lyDetalii);
		numarRandom = new QLineEdit;
		lyDetalii->addRow(new QLabel("Numar random:"), numarRandom);
		butonAddRandom = new QPushButton{ "Cos random" };
		lyDetalii->addWidget(butonAddRandom);
		ly->addWidget(detalii);
		setLayout(ly);
	}

	void connectSignals() {
		c.addObserver(this);
		QObject::connect(butonClear, &QPushButton::clicked, [&]() {
			c.emptyBasket();
			loadList(c.cumparaturi());
		});

		QObject::connect(butonAddRandom, &QPushButton::clicked, [&]() {
			c.randomBasket(numarRandom->text().QString::toDouble());
			loadList(c.cumparaturi());
		});
	}
public:
	CosGUI(CosCumparaturi& c) :c{ c } {
		initGUI();
		connectSignals();
		loadList(c.cumparaturi());
	};
	void update() override {
		loadList(c.cumparaturi());
	}
	~CosGUI() {
		c.removeObserver(this);
	};
};


#pragma once
#include "Produs.h"
#include <vector>
using std::vector;
#include <qdebug.h>
#include<qbrush.h>
#include <QAbstractTableModel>
class TableModel: public QAbstractTableModel
{
	vector<Produs> products;
public:
	TableModel(const vector<Produs>& products) :products{ products } {};
	int rowCount(const QModelIndex& parent = QModelIndex())const override {
		return products.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex())const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
		qDebug << "row: " << index.row() << "col: " << index.column() << "role: " << role;
		if (role == Qt::TextColorRole) {
			Produs p = products[index.row()];
			if (p.getPret() > 0) {
				return QBrush{ Qt::red };
			}
		}
		if (role == Qt::DisplayRole) {
			Produs p = products[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getNume());
			}
			else
				if (index.column() == 1) {
					return QString::fromStdString(p.getTip());
				}
				else
					if (index.column() == 2) {
						return QString::number(p.getPret());
					}
		}
		return QVariant{};
	}

	void setProducts(const vector<Produs> products) {
		this->products = products;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};


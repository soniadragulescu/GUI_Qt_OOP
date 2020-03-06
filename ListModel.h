#pragma once
#include "Produs.h"
#include <qcolor.h>
#include <vector>
#include <qdebug.h>
#include <QAbstractListModel>
using std::vector;
class ListModel : public QAbstractListModel
{
	vector<Produs> products;
public:
	ListModel(const vector<Produs>& products) :products{ products } {};
	int rowCount(const QModelIndex& parent = QModelIndex())const {
		return products.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
		if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto n = products[index.row()].getNume();
			return QString::fromStdString(n);
		}
		if (role == Qt::UserRole) {
			auto t = products[index.row()].getTip();
			return QString::fromStdString(t);
		}

		if (role == Qt::BackgroundRole) {
			if (products[index.row()].getNume()[0] =='p') {
				return QColor(Qt::red);
			}
		}
		return QVariant{};
	}
};


//#include "laborator1011OOP.h"
#include "GUI.h"
#include <QApplication>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qlistwidget.h>
#include "Magazin.h"
void testAll() {
	testProdus();
	testeRepo();
	testValidator();
	testeMagazin();
}
int main(int argc, char *argv[])
{
	//testAll();
	{
		QApplication a(argc, argv);
		
		RepoFile r{ "undeesti.txt" };
		Validator v;
		Magazin m{ r,v };
		GUI gui{ m };

		//laborator1011OOP w;
		//w.show();
		gui.show();
		a.exec();
	}
	return 0;
}

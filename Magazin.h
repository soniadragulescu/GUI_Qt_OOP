#pragma once
#include "RepoFile.h"
#include "ActiuneUndo.h"
#include "Produs.h"
#include "Validator.h"
#include "CosCumparaturi.h"
#include <vector>
using std::vector;
#include <random>
#include <chrono>
class CosCumparaturi;
class ActiuneUndo;
class Magazin
{
	RepoFile& r;
	Validator& v;
	CosCumparaturi c{ r };
	vector<ActiuneUndo*> undoActions;
public:
	Magazin() = delete;
	Magazin(RepoFile& r, Validator& v) :
		r{ r },
		v{ v }{};
	Magazin(const Magazin& m) = delete;
	void adaugaProdus(const string& nume, const string& tip, const double pret, const string& producator);
	void stergeProdus(const string& nume, const string& tip);
	Produs cautaProdus(const string& nume, const string& tip);
	void modificaProdus(const string& nume, const string& tip, const double pretNou);
	const vector<Produs>& getAll() const noexcept;
	void undo();
	vector<Produs> sortByPrice();
	vector<Produs> sortByName();
	vector<Produs> filterPrice(int pret);

	const vector<Produs>& addToCos(const string& nume, const string& tip);
	const vector<Produs>& addRandom(int nr);
	const vector<Produs>& golesteCos();
	const vector<Produs>& toateCumparaturile();

	CosCumparaturi& getCos() {
		return c;
	}

	~Magazin();
};

void testeMagazin();



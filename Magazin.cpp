#include "Magazin.h"
#include <assert.h>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
using std::cout;
void Magazin::adaugaProdus(const string& nume, const string& tip, const double pret, const string& producator) {
	Produs p{ nume, tip, pret, producator };
	v.validate(p);
	r.store(p);
	this->undoActions.push_back(new UndoAdauga{ this->r, p });
}
void Magazin::stergeProdus(const string& nume, const string& tip) {
	Produs p = r.search(Produs{ nume, tip, 0, "" });
	r.remove(p);
	this->undoActions.push_back(new UndoSterge(this->r, p));
}
void Magazin::modificaProdus(const string& nume, const string& tip, const double pretNou) {
	Produs vechi = r.search(Produs{ nume, tip,0,"" });
	Produs nou = vechi;
	nou.setPret(pretNou);
	r.update(vechi, nou);
	this->undoActions.push_back(new UndoModifica(this->r, vechi, nou));
}
Produs Magazin::cautaProdus(const string& nume, const string& tip) {
	return r.search(Produs(nume, tip, 0, ""));
}
const vector<Produs>& Magazin::getAll() const noexcept {
	return r.getAll();
}
void Magazin::undo() {
	if (this->undoActions.empty())
		throw(RepoException("No actions to unde!\n"));
	ActiuneUndo* ua = this->undoActions.back();
	ua->doUndo();
	this->undoActions.pop_back();
	delete ua;
}

vector<Produs> Magazin::sortByPrice() {
	auto v = r.getAll();
	sort(v.begin(), v.end(), [](const Produs&p1, const Produs& p2) {
		return p1.getPret() < p2.getPret();
	});
	return v;
}
vector<Produs> Magazin::sortByName() {
	auto v = r.getAll();
	sort(v.begin(), v.end(), [](const Produs& p1, const Produs& p2) {
		return p1.getNume() <= p2.getNume();
	});
	return v;
}

vector<Produs> Magazin::filterPrice(int pret) {
	vector<Produs> rez;
	auto all = r.getAll();
	copy_if(all.begin(), all.end(), back_inserter(rez), [=](const Produs& p) {
		return p.getPret() > pret;
	});
	return rez;
}

const vector<Produs>& Magazin::addToCos(const string& nume, const string& tip) {
	Produs p = r.search(Produs(nume, tip, 0, ""));
	c.addToBasket(p);
	return c.cumparaturi();
}
const vector<Produs>& Magazin::addRandom(int nr) {
	c.randomBasket(nr);
	return c.cumparaturi();
}
const vector<Produs>& Magazin::golesteCos() {
	c.emptyBasket();
	return c.cumparaturi();
}
const vector<Produs>& Magazin::toateCumparaturile() {
	return c.cumparaturi();
}

Magazin::~Magazin() {
	for (ActiuneUndo* ua : this->undoActions) {
		delete ua;
	}
}

void testeMagazin() {
	//test service

	RepoFile r("testMagazin.txt");
	Validator v;
	Magazin m{ r, v };
	cout << "marime magazin: " << m.getAll().size() << '\n';
	assert(m.getAll().size() == 0);
	m.adaugaProdus("paine", "integrala", 3.8, "panemar");
	assert(m.getAll().size() == 1);
	try {
		m.adaugaProdus("paine", "integrala", 10, "velPitar");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
	}
	m.modificaProdus("paine", "integrala", 10);
	Produs p = m.cautaProdus("paine", "integrala");
	assert(p.getNume() == "paine");
	assert(p.getPret() == 10);
	try {
		m.cautaProdus("a", "a");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
	}
	m.stergeProdus("paine", "integrala");
	assert(m.getAll().size() == 0);
	try {
		m.stergeProdus("a", "a");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
	}
	//teste cos

	//teste undo
	assert(m.getAll().size() == 0);
	m.adaugaProdus("paine1", "integrala1", 3.8, "panemar1");
	m.adaugaProdus("paine2", "integrala2", 4.2, "panemar2");
	m.adaugaProdus("paine3", "integrala3", 5, "panemar3");
	assert(m.getAll().size() == 3);
	m.undo();
	assert(m.getAll().size() == 2);
	m.stergeProdus("paine1", "integrala1");
	assert(m.getAll().size() == 1);
	m.undo();
	assert(m.getAll().size() == 2);
	assert(m.cautaProdus("paine1", "integrala1").getPret() == 3.8);
	m.modificaProdus("paine1", "integrala1", 10);
	assert(m.cautaProdus("paine1", "integrala1").getPret() == 10);
	m.undo();
	assert(m.cautaProdus("paine1", "integrala1").getPret() == 3.8);
	m.stergeProdus("paine1", "integrala1");
	m.stergeProdus("paine2", "integrala2");
}
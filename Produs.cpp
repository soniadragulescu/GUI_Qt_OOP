#include "Produs.h"
#include <assert.h>

const string& Produs::getNume() const {
	return this->nume;
}
const string& Produs::getTip()const {
	return this->tip;
}
const double& Produs::getPret() const {
	return this->pret;
}
const string& Produs::getProducator() const {
	return this->producator;
}

void Produs::setNume(const string& numeNou) {
	this->nume = numeNou;
}
void Produs::setTip(const string& tipNou) {
	this->tip = tipNou;
}
void Produs::setPret(const double& pretNou) {
	this->pret = pretNou;
}
void Produs::setProducator(const string& producatorNou) {
	this->producator = producatorNou;
}

std::istream& operator>>(std::istream& f, Produs& p) {
	string nume, tip, producator;
	double pret;
	f >> p.nume >> p.tip >> p.pret >> p.producator;
	return f;
}
std::ostream& operator<<(std::ostream& g, const Produs& p) {
	g << p.nume << ' ' << p.tip << ' ' << p.pret << ' ' << p.producator;
	return g;
}

void testProdus() {
	Produs p{ "paine","integrala",3.8,"panemar" };
	Produs p2{ p };
	assert(p.getNume() == "paine");
	assert(p.getTip() == "integrala");
	assert(p.getPret() == 3.8);
	assert(p.getProducator() == "panemar");
	assert(p2.getNume() == "paine");
	assert(p2.getTip() == "integrala");
	assert(p2.getPret() == 3.8);
	assert(p2.getProducator() == "panemar");

}

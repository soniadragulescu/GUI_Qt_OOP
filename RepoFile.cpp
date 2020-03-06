#include "RepoFile.h"
//#include <utility>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>
using std::ifstream;
using std::ofstream;
using std::endl;
//using namespace std;

void RepoFile::readAllFromFile() {
	this->elems.clear();
	ifstream f(this->filename);
	if (!f.is_open()) {
		throw RepoException("Fisier negasit");
	}
	Produs p;
	while (f >> p) {
		this->elems.push_back(p);
	}
#
	f.close();
}
void RepoFile::writeAllToFile() {
	ofstream g(this->filename);
	for (const auto&p : this->elems) {
		g << p << endl;
	}
	g.close();
}
void RepoFile::store(const Produs& p) {
	this->readAllFromFile();
	auto it = find(this->elems.begin(), this->elems.end(), p);
	if (it == this->elems.end()) {
		this->elems.push_back(p);
	}
	else
		throw RepoException("Produs existent!\n");
	this->writeAllToFile();
}
const Produs RepoFile::search(const Produs& p) {
	this->readAllFromFile();
	auto it = find(this->elems.begin(), this->elems.end(), p);
	if (it != this->elems.end())
		return *it;
	else
		throw RepoException("Nu exista produsul!\n");
}
void RepoFile::remove(const Produs& p) {
	this->readAllFromFile();
	auto it = find(this->elems.begin(), this->elems.end(), p);
	if (it != this->elems.end()) {
		this->elems.erase(it);
		this->writeAllToFile();
	}
	else
		throw RepoException("Nu exista produsul!\n");

}
void RepoFile::update(const Produs& vechi, const Produs& nou) {
	this->readAllFromFile();
	auto it = find(this->elems.begin(), this->elems.end(), vechi);
	if (it != this->elems.end()) {
		*it = nou;
		this->writeAllToFile();
	}
	else
		throw RepoException("Nu exista produsul!\n");
}
const vector<Produs>& RepoFile::getAll() const noexcept {
	//this->readAllFromFile();
	return this->elems;
}

void testeRepo() {
	RepoFile r("testeRepo.in");
	assert(r.getAll().size() == 0);
	Produs p{ "paine","integrala",3.8,"panemar" };
	r.store(p);
	assert(r.getAll().size() == 1);
	try {
		r.store(p);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	Produs p2(r.search(p));
	assert(p2.getNume() == p.getNume());
	assert(r.search(p).getPret() == 3.8);
	p2.setPret(10);
	r.update(p, p2);
	assert(r.search(p).getPret() == 10);
	r.remove(p);
	assert(r.getAll().size() == 0);

}

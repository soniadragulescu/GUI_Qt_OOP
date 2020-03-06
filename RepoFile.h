#pragma once
#include <vector>
#include <string>
#include "Produs.h"
using std::string;
using std::ostream;
using std::vector;
class RepoException {
	string mesaj;
public:
	RepoException(string m) :mesaj{ m } {};
	friend ostream& operator<<(ostream& out, const RepoException& ex) {
		out << ex.mesaj;
		return out;
	}
};
class RepoFile
{
protected:
	vector<Produs> elems;
	string filename;
	void readAllFromFile();
	void writeAllToFile();
public:
	RepoFile(const string& filename) :filename{ filename } {
		this->readAllFromFile();
	};
	RepoFile(const RepoFile& ot) = delete;
	void store(const Produs& p);
	const Produs search(const Produs& p);
	void remove(const Produs& p);
	void update(const Produs& vechi, const Produs& nou);
	const vector<Produs>& getAll()const noexcept;
	~RepoFile() = default;
};

void testeRepo();


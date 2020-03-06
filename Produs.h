#pragma once
#include <string>
using std::string;

class Produs
{
	string nume;
	string tip;
	double pret;
	string producator;
public:
	Produs(const string nume, const string tip, const double pret, const string producator) :
		nume{ nume },
		tip{ tip },
		pret{ pret },
		producator{ producator }{};
	Produs() :
		nume{ "nume0" },
		tip{ "tip0" },
		pret{ 0 },
		producator{ "producator" }{};
	Produs(const Produs& ot) :
		nume{ ot.nume },
		tip{ ot.tip },
		pret{ ot.pret },
		producator{ ot.producator }{}

	const string& getNume() const;
	const string& getTip()const;
	const double& getPret() const;
	const string& getProducator() const;

	bool operator==(const Produs& other) {
		return this->nume == other.nume&&this->tip == other.tip;
	}

	void setNume(const string& numeNou);
	void setTip(const string& tipNou);
	void setPret(const double& pretNou);
	void setProducator(const string& producatorNou);

	friend std::istream& operator>>(std::istream&, Produs&);
	friend std::ostream& operator<<(std::ostream&, const Produs&);
	~Produs() = default;
};

void testProdus();


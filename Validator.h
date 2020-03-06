#pragma once
#include "Produs.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ostream;

class ValidatorException {
	vector<string>mesaje;
public:
	ValidatorException(const vector<string>& errors) :
		mesaje{ errors } {};
	friend ostream& operator<<(ostream& out, const ValidatorException& ex);
	std::string getMsg() {
		return mesaje[0];
	}
};
class Validator
{

public:
	void validate(Produs& p);
};

void testValidator();


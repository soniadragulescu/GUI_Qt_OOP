#include "Validator.h"
#include <assert.h>

ostream & operator<<(ostream & out, const ValidatorException & ex)
{
	for (const auto& m : ex.mesaje) {
		out << m << ' ';
	}
	out << '\n';
	return out;
}

void Validator::validate(Produs & p)
{
	vector<string>errors;
	if (p.getNume() == "")
		errors.push_back("Nume vid!");
	if (p.getTip() == "")
		errors.push_back("Tip vid!");
	if (p.getPret() < 0)
		errors.push_back("Pret negativ!");
	if (p.getProducator() == "")
		errors.push_back("Producator vid!");
	if (errors.size() > 0)
		throw ValidatorException(errors);

}

void testValidator() {
	Validator v;
	Produs p{ "","",-3.2,"" };
	try {
		v.validate(p);
		assert(false);
	}
	catch (ValidatorException&) {
		assert(true);

	}

}
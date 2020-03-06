#pragma once
#include "RepoFile.h"
#include "Produs.h"
#include <vector>
using std::vector;
#include <random>
#include <chrono>
#include "observer.h"

class CosCumparaturi:public Observable
{
private:
	vector<Produs> cos;
	const RepoFile& r;
public:
	CosCumparaturi(const RepoFile& r) :r{ r } {
		this->emptyBasket();
	};
	void emptyBasket() {
		cos.clear();
		notify();
	}

	void addToBasket(const Produs& p) {
		cos.push_back(p);
		notify();
	}

	void randomBasket(int nr) {
		/*std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, nr);
		int randomNr = distribution(generator);*/
		vector<Produs> all = r.getAll();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while (cos.size() < nr && all.size() > 0) {
			cos.push_back(all.back());
			all.pop_back();
		}
		notify();
	}

	int basketSize() const noexcept {
		return cos.size();
	}

	const vector<Produs>& cumparaturi() {
		return cos;
	}

	~CosCumparaturi() = default;
};


#pragma once
#include <vector>
using std::vector;
#include <algorithm>
class Observer
{
public:
	virtual void update() = 0;
};

class Observable {
	vector<Observer*> observers;
public:
	void addObserver(Observer* o) {
		observers.push_back(o);
	}

	void removeObserver(Observer* o) {
		observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
	}

	void notify() {
		for (auto o : observers) {
			o->update();
		}
	}
};


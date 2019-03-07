#pragma once
#include <vector>
#include <assert.h>
using namespace std;
class Observer
{
public:
	virtual void update() = 0;
	~Observer() = default;
};

class Observable {
private:
	vector<Observer*> observers;
public:

	void notifyAll() {
		for (auto obs : observers)
			obs->update();
	}

	void addObserver(Observer* ob) {
		observers.push_back(ob);
	}
};


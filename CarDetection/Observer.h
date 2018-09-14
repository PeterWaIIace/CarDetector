#pragma once

#include <list>
#include <QString>

class Observer
{
public:
	Observer() {}
	virtual void update(QString str) = 0;
};

class Watched
{
public:
	std::list<Observer*> allObservers;
	Watched() {}
	void addObserver(Observer* observer);
	void delObserver(Observer* observer);
	void NotifyObserver();
};


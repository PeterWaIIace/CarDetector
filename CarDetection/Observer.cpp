#include "Observer.h"


void Watched::addObserver(Observer *observer) {
	this->allObservers.push_front(observer);

}
void Watched::delObserver(Observer *observer) {
	this->allObservers.remove(observer);

}

void Watched::NotifyObserver() {
	for (Observer* i : this->allObservers) {
		QString data = "example";
		i->update(data);
	}
}

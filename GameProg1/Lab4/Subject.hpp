#ifndef HPP_SUBJECT
#define HPP_SUBJECT

#include <set>
#include "Observer.hpp"
#include "Event.hpp"

class Subject
{
public:
	void addObserver(Observer&);

	void removeObserver(Observer&);

	virtual void notify(::Event const&);

private:
	std::set<Observer*> observers;

};

#endif HPP_SUBJECT
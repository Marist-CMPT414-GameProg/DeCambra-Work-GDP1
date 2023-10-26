#include "Subject.hpp"

void Subject::addObserver(Observer& o) 
{
    observers.insert(&o);
}

void Subject::removeObserver(Observer& o) 
{
    observers.erase(&o);
}

void Subject::notify(::Event const& ev) // take in an event object
{
    for (Observer* o : observers)
    {
        o->onNotify(ev);
    }
}
#ifndef HPP_SUBJECT
#define HPP_SUBJECT

#include <set>
#include "Observer.hpp"

/// <summary>
/// Interface for objects that are observed by other objects.
/// </summary>
/// <typeparam name="E">indicates the type of Event data sent</typeparam>
template <typename E>
class Subject {
public:
    /// <summary>
    /// Register a new observer object watching this subject.
    /// </summary>
    /// <param name="o">an object interested in changes to this subject</param>
    void addObserver(Observer<E>&);

    /// <summary>
    /// Remove the given observer from the list of watchers for this subject.
    /// </summary>
    /// <param name="o">an object no longer interested in changes to this subject</param>
    void removeObserver(Observer<E>&);

    /// <summary>
    /// Notify all observers watching this object of any events on this subject.
    /// </summary>
    virtual void notify(E const&);

private:
    // Note: vector<> and list<> are also possible choices here depending on our needs
    std::set<Observer<E>*> observers;
};

/* IMPLEMENTATION */

template <typename E>
void Subject<E>::addObserver(Observer<E>& o) {
    observers.insert(&o);
}

template <typename E>
void Subject<E>::removeObserver(Observer<E>& o) {
    observers.erase(&o);
}

template <typename E>
void Subject<E>::notify(E const& event) {
    for (Observer<E>* o : observers) {
        o->onNotify(event);
    }
}

#endif HPP_SUBJECT

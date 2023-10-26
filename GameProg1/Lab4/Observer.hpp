#ifndef HPP_OBSERVER
#define HPP_OBSERVER

struct Event;

class Observer
{
public:
    virtual void onNotify(::Event const& ev) = 0;
};

#endif HPP_OBSERVER
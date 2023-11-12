#ifndef HPP_BUTTON
#define HPP_BUTTON

#include "GameObject.hpp"
#include "Subject.hpp"

struct TriggerEvent
{
    TriggerEvent(int n) : value(n) {}
    int const value;
};

class Trigger : public GameOrb, public Subject<TriggerEvent>
{
public:
    Trigger(sf::Color const&, sf::Vector2f const&);
    void onNotify(CollisionEvent const& event) override;
};

#endif HPP_BUTTON

#include "Trigger.hpp"
#include "Player.hpp"
#include "SimplePhysics.hpp"
#include <iostream>
#include <typeinfo>

using namespace sf;

Trigger::Trigger(Color const& color, Vector2f const& position)
    : GameOrb(color, 32.0f, position) {}

void Trigger::onNotify(CollisionEvent const& event)
{
    if (typeid(event.other) != typeid(Player)) { return; }

    if (shape.getFillColor() == Color::Red) {
        notify(TriggerEvent(1));
    }
    else if (shape.getFillColor() == Color::Green) {
        notify(TriggerEvent(2));
    }
    else if (shape.getFillColor() == Color::Blue) {
        notify(TriggerEvent(3));
    }

}

#include "Bee.hpp"
#include "BeeStates.hpp"

using sf::Time;
using sf::Vector2f;

// TODO Start the Bee in the idle state
Bee::Bee(Vector2f const& center, Vector2f const& position)
    : GameSprite("graphics/bee.png", position), center(center), currentState(nullptr)
{
    currentState = new IdleState(*this);
}

void
Bee::onNotify(TriggerEvent const& event)
{
    // TODO Let the current state handle the event and change state if appropriate
    State* newState = currentState->handleEvent(event);
    // if new state is different from current state?
    // if so, exit the current state
    // set the new state as my current state
    // and enter the current state
    if (newState != nullptr) 
    {
        currentState->exit();
        delete currentState;
        currentState = newState;
        currentState->enter();
    }
}

void
Bee::update(Time const& dt)
{
    // TODO Update the current state
    // if if if if if if
    currentState->update(dt.asSeconds());

    if (velocity.x == 0 && velocity.y == 0) { return; }

    Vector2f prevPosition = sprite.getPosition();
    Vector2f newPosition = prevPosition + dt.asSeconds() * speed * velocity;
    sprite.setPosition(newPosition);
}

sf::Vector2f Bee::getPosition()
{
    return sprite.getPosition();
}
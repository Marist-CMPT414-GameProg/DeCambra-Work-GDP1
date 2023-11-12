#include "BeeStates.hpp"
#include "Trigger.hpp"
#include "VectorMath.hpp"

#include <cmath>
#include <iostream>

using sf::Sprite;
using sf::Vector2f;

/* Forward declarations of auxiliary functions */

bool coinflip();
float random();

Bee::State::State(Bee& bee) : controlledBee(bee) {}

// TODO Implement your derives Bee states here

// Idle State
Bee::IdleState::IdleState(Bee& bee) : Bee::State(bee) {}

void Bee::IdleState::enter()
{
    // Stop the bee from moving (i.e., make its velocity 0)
    controlledBee.velocity = sf::Vector2f(0.f, 0.f);
}

void Bee::IdleState::exit() {}

Bee::State* 
Bee::IdleState::handleEvent(TriggerEvent const& trigger)
{
    // check value of target of the trigger event
    // and then decide what state to return
    switch (trigger.value)
    {
    case 1: return nullptr;
    case 2: return new OrbitState(controlledBee);
    case 3: return new WanderState(controlledBee);
    }
}

void Bee::IdleState::update(float dt) {}

// Orbit State
Bee::OrbitState::OrbitState(Bee& bee) : Bee::State(bee) {}

void Bee::OrbitState::enter() 
{
    // Get flower center
    controlledBee.center = sf::Vector2f(1280, 720);
}

void Bee::OrbitState::exit() {}

Bee::State* 
Bee::OrbitState::handleEvent(TriggerEvent const& trigger)
{
    // check value of target of the trigger event
    // and then decide what state to return
    
    switch (trigger.value)
    {
    case 1: return new IdleState(controlledBee);
    case 2: return nullptr;
    case 3: return new WanderState(controlledBee);
    }
}

void Bee::OrbitState::update(float dt) 
{
    // Orbit around the flower
    sf::Vector2f toFlower = controlledBee.center - controlledBee.getPosition();

    // Rotate the toFlower vector manually by -90 degrees (ya, -xa)
    sf::Vector2f rotatedToFlower(-toFlower.y, toFlower.x);

    // Normalize the rotated vector to maintain constant speed
    normalize(rotatedToFlower);

    // Update bee position based on the orbit
    controlledBee.sprite.setPosition(controlledBee.getPosition() + dt * controlledBee.speed * rotatedToFlower);
}


// WanderState
Bee::WanderState::WanderState(Bee& bee) : Bee::State(bee) {}

void Bee::WanderState::enter() 
{
    // Get flower center
    controlledBee.center = sf::Vector2f(1280, 720);
}

void Bee::WanderState::exit() {}

Bee::State* 
Bee::WanderState::handleEvent(TriggerEvent const& trigger) 
{
    switch (trigger.value)
    {
    case 1: return new IdleState(controlledBee);
    case 2: return new OrbitState(controlledBee);
    case 3: return nullptr;
    }
}

void Bee::WanderState::update(float dt) 
{
    // Get a random direction
    sf::Vector2f randomDirection(random() - 0.5f, random() - 0.5f);

    // Normalize the random direction
    normalize(randomDirection);

    // Update bee position based on the new position
    controlledBee.sprite.setPosition(controlledBee.getPosition() + dt * controlledBee.speed * randomDirection);
}
// ...
/* Auxiliary functions */

bool
coinflip()
{
    constexpr static int HALF_MAX = RAND_MAX / 2;
    return rand() < HALF_MAX;
}

float
random()
{
    return rand() / float(RAND_MAX);
}

#include "Player.hpp"
#include "TextureHolder.hpp"
#include "VectorMath.hpp"
#include <iostream>

using namespace sf;

// Hidden constants - not exposed in the header file
int const LEFT = 0x08; // 1000
int const RIGHT = 0x04; // 0100
int const UP = 0x02; // 0010
int const DOWN = 0x01; // 0001

// Forward declarations of helper functions
Vector2f dirToVec(int dirCode);

Player::Player(Vector2f const& position)
    : GameSprite("graphics/hand.png", Vector2f(0, 0)), dirCode(0), prevPosition(position)
{
    sprite.setPosition(prevPosition);
}

void
Player::update(sf::Time const& dt)
{
    if (velocity.x == 0 && velocity.y == 0) { return; }

    prevPosition = sprite.getPosition();

    Vector2f newPosition = prevPosition + dt.asSeconds() * speed * velocity;
    sprite.setPosition(newPosition);
}

void
Player::cancelMove()
{
    sprite.setPosition(prevPosition);
}

void Player::onNotify(CollisionEvent const& collision)
{
    cancelMove();
}

void
Player::handleInput(Event const& event)
{
    if (event.type == Event::KeyPressed) {
        handleKeyEvent(event.key, true);
    }
    else if (event.type == Event::KeyReleased) {
        handleKeyEvent(event.key, false);
    }
}

void
Player::handleKeyEvent(Event::KeyEvent key, bool isPressed)
{
    switch (key.code) {
    case Keyboard::W:
        isPressed ? move(UP) : stop(UP ^ 0xFFFF);
        break;
    case Keyboard::S:
        isPressed ? move(DOWN) : stop(DOWN ^ 0xFFF);
        break;
    case Keyboard::A:
        isPressed ? move(LEFT) : stop(LEFT ^ 0xFFFF);
        break;
    case Keyboard::D:
        isPressed ? move(RIGHT) : stop(RIGHT ^ 0xFFFF);
        break;
    }
}

void Player::move(int dir)
{
    dirCode |= dir;
    velocity = dirToVec(dirCode);
    normalize(velocity); // normalize to unit length so Player is not faster on diagnonals
}

void Player::stop(int dirMask)
{
    dirCode &= dirMask;
    velocity = dirToVec(dirCode);
    normalize(velocity); // normalize to unit length so Player is not faster on diagnonals
}

/* Auxiliary/helper functions */

inline Vector2f
dirToVec(int dirCode)
{
    // convert dirCode bit-code to a 2D vector
    int dx = ((RIGHT & dirCode) >> 2) - ((LEFT & dirCode) >> 3);
    int dy = (DOWN & dirCode) - ((UP & dirCode) >> 1);
    Vector2f dv(dx, dy);
    return dv;
}

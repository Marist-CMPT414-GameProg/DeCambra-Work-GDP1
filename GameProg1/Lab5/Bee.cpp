#include "Bee.h"
#include "TextureHolder.h"

using namespace sf;

// Hidden constants (in the CPP file and not exposed in the header)
int const LEFT = 0x08; // 1000 (>>3) 0001
int const RIGHT = 0x04; // 0100 (>>2) 0001
int const UP = 0x02; // 0010 (>>1) 0001
int const DOWN = 0x01; // 0001 (>>0) 0001

Vector2f dirToVec(int dirCode)
{
    int dx = ((RIGHT & dirCode) >> 2) - ((LEFT & dirCode) >> 3);
    int dy = (DOWN & dirCode) - ((UP & dirCode) >> 1);
    Vector2f dv(dx, dy);
    return dv;
}

void normalize(Vector2f& a)
{
    float d = sqrt(a.x * a.x + a.y * a.y);
    a = a / d;
}

Bee::Bee(Vector2f const& position)
    : GameObject("graphics/bee.png", Vector2f(0, 0)), velocity()
{}

void Bee::update(sf::Time const& dt)
{
    prevPosition = sprite.getPosition();
    Vector2f newPosition = prevPosition + dt.asSeconds() * speed * velocity;
    sprite.setPosition(newPosition);
}

void Bee::handleInput(Event const& event)
{
    if (event.type == Event::KeyPressed) 
    {
        handleKeyEvent(event.key, true);
    }
    else if (event.type == Event::KeyReleased) 
    {
        handleKeyEvent(event.key, false);
    }
}

void Bee::handleKeyEvent(Event::KeyEvent key, bool isPressed)
{
    switch (key.code) 
    {
    case Keyboard::W:
        isPressed ? moveUp() : stopUp();
        break;
    case Keyboard::S:
        isPressed ? moveDown() : stopDown();
        break;
    case Keyboard::A:
        isPressed ? moveLeft() : stopLeft();
        break;
    case Keyboard::D:
        isPressed ? moveRight() : stopRight();
        break;
    }
}

void Bee::cancelMove()
{
    sprite.setPosition(prevPosition);
}

void Bee::moveLeft()
{
    dirCode |= LEFT;
    velocity = dirToVec(dirCode);
}

void Bee::moveRight()
{
    dirCode |= RIGHT;
    velocity = dirToVec(dirCode);
}

void Bee::moveUp()
{
    dirCode |= UP;
    velocity = dirToVec(dirCode);
}

void Bee::moveDown()
{
    dirCode |= DOWN;
    velocity = dirToVec(dirCode);
}

void Bee::stopLeft()
{
    dirCode &= (LEFT ^ 0xFFFF);
    velocity = dirToVec(dirCode);
}

void Bee::stopRight()
{
    dirCode &= (RIGHT ^ 0xFFFF);
    velocity = dirToVec(dirCode);
}

void Bee::stopUp()
{
    dirCode &= (UP ^ 0xFFFF);
    velocity = dirToVec(dirCode);
}

void Bee::stopDown()
{
    dirCode &= (DOWN ^ 0xFFFF);
    velocity = dirToVec(dirCode);
}
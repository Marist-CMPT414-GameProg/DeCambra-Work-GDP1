#ifndef HPP_SIMPLEPHYSICS
#define HPP_SIMPLEPHYSICS

#include <SFML/Graphics/Rect.hpp>
#include "GameObject.hpp"

struct CollisionEvent
{
    CollisionEvent(GameObject& other, sf::FloatRect const& intersection);
    GameObject& other;
    sf::FloatRect const intersection;
};

struct Physics
{
    static void checkCollisions(GameObjArray const& gameObjects);
};

#endif HPP_SIMPLEPHYSICS

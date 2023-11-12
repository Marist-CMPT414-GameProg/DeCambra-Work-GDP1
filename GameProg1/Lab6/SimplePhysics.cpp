#include "SimplePhysics.hpp"
#include "GameObject.hpp"

inline CollisionEvent::CollisionEvent(GameObject& other, sf::FloatRect const& intersection)
    : other(other), intersection(intersection) {}

void Physics::checkCollisions(GameObjArray const& gameObjects)
{
    for (auto obj1 : gameObjects) {
        if (obj1 == nullptr) { continue; }

        for (auto obj2 : gameObjects) {
            if (obj2 == nullptr || obj1 == obj2) { continue; }

            sf::FloatRect intersection;
            if (obj1->getCollider().intersects(obj2->getCollider(), intersection)) {
                obj1->onNotify(CollisionEvent(*obj2, intersection));
                obj2->onNotify(CollisionEvent(*obj1, intersection));
            }
        }
    }
}

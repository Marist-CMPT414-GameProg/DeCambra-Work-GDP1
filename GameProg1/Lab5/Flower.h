#ifndef HPP_FLOWER
#define HPP_FLOWER

#include "GameObject.h"
#include <SFML/System/Vector2.hpp>

struct Flower : public GameObject
{
	Flower(sf::Vector2f const&);

	void update(sf::Time const&);
};

#endif HPP_FLOWER
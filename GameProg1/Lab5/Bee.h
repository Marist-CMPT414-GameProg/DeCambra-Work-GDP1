#ifndef HPP_BEE
#define HPP_BEE

#include "GameObject.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Bee : public GameObject
{
public:
	Bee(sf::Vector2f const&);

	void handleInput(sf::Event const& event);
	void handleKeyEvent(sf::Event::KeyEvent key, bool isPressed);
	void update(sf::Time const&);
	void cancelMove();

private:
	float speed = 300.0f;
	sf::Vector2f velocity;
	sf::Vector2f prevPosition;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
};

#endif HPP_BEE
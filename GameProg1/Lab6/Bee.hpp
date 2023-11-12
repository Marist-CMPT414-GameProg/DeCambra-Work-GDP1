#ifndef HPP_BEE
#define HPP_BEE

#include "GameObject.hpp"

struct TriggerEvent;


class Bee
	: public GameSprite
	, public Observer<TriggerEvent>
{
	struct State; // Forward declaration of inner base-class for Bee states
public:
	Bee(sf::Vector2f const&, sf::Vector2f const&);
	void onNotify(TriggerEvent const&);
	void update(sf::Time const& dt) override;
	sf::Vector2f getPosition();
private:
	float speed = 500;
	sf::Vector2f center;
	sf::Vector2f velocity;
	State* currentState;

	// TODO Add forward declarations of inner structs for your derived states here
	struct IdleState;
	struct OrbitState;
	struct WanderState;
};

#endif HPP_BEE
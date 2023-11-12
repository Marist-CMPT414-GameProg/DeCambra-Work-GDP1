#ifndef HPP_PLAYER
#define HPP_PLAYER

#include "GameObject.hpp"
#include "Observer.hpp"

/// <summary>
/// Simple bee character controllable via keyboard input
/// </summary>
class Player : public GameSprite
{
public:
    /// <summary>
    /// Initialize a new bee at the given position
    /// </summary>
    /// <param name="position">starting position of the new bee</param>
    Player(sf::Vector2f const&);

	/// <summary>
	/// Reset the bee back to its previous position (i.e., from the previous frame)
	/// </summary>
	void cancelMove();

	void onNotify(CollisionEvent const& collision);

	void handleInput(sf::Event const& event);
	void update(sf::Time const&);

private:
	int dirCode;
	float speed = 500.0f;
	sf::Vector2f prevPosition;
	sf::Vector2f velocity;

	void handleKeyEvent(sf::Event::KeyEvent key, bool isPressed);

	void move(int dir);
	void stop(int dir);
};

#endif HPP_PLAYER

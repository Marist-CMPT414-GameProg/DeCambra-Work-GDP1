#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Crate.h"
#include "Fire.h"

using namespace sf;

class Zombie
{
private:
	int zombieType;

	// How fast is each zombie type?
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	float walkTime;
	float waitTime;
	float timeMoving = 0;
	float timeUntilMove = 0;

	// How tough is each zombie type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// Where is this zombie?
	Vector2f m_Position;

	// A sprite for the zombie
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;
	float tempSpeed;

	// How much health has it got?
	float m_Health;

	int m_Time;

	// When was the zombie last hit
	Time m_LastHit;

	// Is it still alive?
	bool m_Alive;

	// Increase the crawlers speed
	float speedMultiplier = 1.0f;

	// Public prototypes go here	
public:

	// Handle when a bullet hits a zombie
	bool hit();

	bool burn(Time timehit, Sound& burnSound);

	// Handle increasing the crawlers speed
	void increaseSpeed();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation, std::vector<Crate>& crates, std::vector<Fire>& fires, Time timeHit, Sound& burnSound);
};
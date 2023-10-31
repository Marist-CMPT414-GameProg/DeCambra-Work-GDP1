#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{

	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));

		zombieType = 0;
		m_Speed = BLOATER_SPEED;
		tempSpeed = BLOATER_SPEED;
		walkTime = 500;
		walkTime = 250;
		m_Health = BLOATER_HEALTH;
		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));

		zombieType = 1;
		m_Speed = CHASER_SPEED;
		tempSpeed = CHASER_SPEED;
		walkTime = 250;
		walkTime = 125;
		m_Health = CHASER_HEALTH;
		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));

		zombieType = 2;
		m_Speed = CRAWLER_SPEED;
		tempSpeed = CRAWLER_SPEED;
		walkTime = 1000;
		walkTime = 500;
		m_Health = CRAWLER_HEALTH;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	speedMultiplier = 1.0f;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

void Zombie::increaseSpeed()
{
	// Increase the crawler's speed by 60%
	speedMultiplier = 1.6f;
	tempSpeed *= speedMultiplier;
	// Update the zombie's speed accordingly.
	m_Speed = tempSpeed;
}

bool Zombie::hit()
{
	m_Health--;

	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));

		return true;
	}
	
	// If the crawler is hit increase its speed
	if (zombieType == 2)
	{
		increaseSpeed();
	}

	// injured but not dead yet
	return false;
}

bool Zombie::burn(Time timeHit, Sound& burnSound)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 2 * m_Time)
	{
		m_LastHit = timeHit;
		m_Health -= 1;
		burnSound.play();
	}
	else
	{
		return false;
	}
}

bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation, std::vector<Crate>& crates, std::vector<Fire>& fires, Time timeHit, Sound& burnSound)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	timeMoving += 0.5;
	
	Vector2f previousPosition = m_Position;

	// Update the zombie position variables
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x + m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y + m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x - m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y - m_Speed * elapsedTime;
	}

	// Check for collisions with crates
	for (Crate& crate : crates)
	{
		if (m_Position.x < crate.getPosition().left + crate.getPosition().width &&
			m_Position.x + m_Sprite.getGlobalBounds().width > crate.getPosition().left &&
			m_Position.y < crate.getPosition().top + crate.getPosition().height &&
			m_Position.y + m_Sprite.getGlobalBounds().height > crate.getPosition().top)
		{
			// Handle the collision here, for example, prevent the zombie from moving into the crate
			m_Position = previousPosition;
		}
	}

	// Check if burning
	for (Fire& fire : fires)
	{
		if (m_Position.x < fire.getPosition().left + fire.getPosition().width &&
			m_Position.x + m_Sprite.getGlobalBounds().width > fire.getPosition().left &&
			m_Position.y < fire.getPosition().top + fire.getPosition().height &&
			m_Position.y + m_Sprite.getGlobalBounds().height > fire.getPosition().top)
		{
			if (burn(timeHit, burnSound))
			{
				burn(timeHit, burnSound);
			}
		}
	}

	if (timeMoving >= walkTime) 
	{
		timeUntilMove += .5;
		m_Speed = 0;

		if (timeUntilMove >= waitTime) 
		{
			timeUntilMove = 0;
			timeMoving = 0;
			m_Speed = tempSpeed;
		}
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141;

	m_Sprite.setRotation(angle);
}
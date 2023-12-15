#include "Engine.h"
#include <iostream>

bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;
	// Make a rect for all his parts
	FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = (int)(detectionZone.top / TILE_SIZE) + 4;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0)
	{
		startX = 0;
	}
	if (startY < 0)
	{
		startY = 0;
	}
	if (endX >= m_LM.getLevelSize().x)
	{
		endX = m_LM.getLevelSize().x;
	}
	if (endY >= m_LM.getLevelSize().y)
	{
		endY = m_LM.getLevelSize().y;
	}

	// Has the character fallen out of the map?
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		// respawn the character
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			// Is character colliding with an ice block?
			if (m_ArrayLevel[y][x] == 5)
			{
				if (character.getFeet().intersects(block))
				{
					// Set the character on ice
					character.setOnIce(true);

					character.handleIceBlock(true);
					character.stopFalling(block.top);					

					std::cout << "Is character on ice? " << (character.isOnIce() ? "Yes" : "No") << std::endl;
				}
			}

			// Has character been burnt or drowned?
			// Use head as this allows him to sink a bit
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2)// Fire, ouch!
					{
						// Play a sound
						m_SM.playFallInFire();
					}
					else // Water
					{
						// Play a sound
						m_SM.playFallInWater();
					}
				}
			}

			// Is character colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}
				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
				std::cout << "Is character on ice? " << (character.isOnIce() ? "Yes" : "No") << std::endl;
			}

			// Has the characters' feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this
			// by seeing if an effect is already running			
			// Water tile
			if (m_ArrayLevel[y][x] == 3) 
			{
				if (character.getFeet().intersects(block)) 
				{
					m_WaterParticles.emitParticles(character.getCenter());
				}
			}
			// Fire tile
			else if (m_ArrayLevel[y][x] == 2) 
			{
				if (character.getFeet().intersects(block)) 
				{
					m_FireParticles.emitParticles(character.getCenter());
				}
			}
			// Ice tile
			else if (m_ArrayLevel[y][x] == 5) 
			{
				if (character.getFeet().intersects(block)) 
				{
					m_IceParticles.emitParticles(character.getCenter());
				}
			}
			else if (m_ArrayLevel[y][x] == 4)
			{
				if (character.getFeet().intersects(block))
				{
					m_GoalParticles.emitParticles(character.getCenter());
				}
			}

			// Has the character reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				// Character has reached the goal
				reachedGoal = true;
			}
		}
	}
	// Set the character off ice if not on an ice block
	character.setOnIce(false);

	// All done, return, wheteher or not a new level might be required
	return reachedGoal;
}
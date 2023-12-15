#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		// Load a level
		loadLevel();
	}

	if (m_Playing)
	{
		// Update Thomas
		m_Thomas.update(dtAsSeconds);

		// Update Bob
		m_Bob.update(dtAsSeconds);

		// Update John
		m_John.update(dtAsSeconds);

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob) || detectCollisions(m_John) && detectCollisions(m_Bob) || detectCollisions(m_Thomas) && detectCollisions(m_John))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}
		else
		{
			// Run bobs collision detection
			detectCollisions(m_Bob);
			detectCollisions(m_John);
		}

		// Let bob and thomas jump on each others heads
		if (m_Bob.getFeet().intersects(m_Thomas.getHead())) // bob on thoms
		{
			m_Bob.stopFalling(m_Thomas.getHead().top);
		}
		else if (m_Thomas.getFeet().intersects(m_Bob.getHead())) // thomas on bob
		{
			m_Thomas.stopFalling(m_Bob.getHead().top);
		}
		else if (m_Bob.getFeet().intersects(m_John.getHead())) // bob on john
		{
			m_Bob.stopFalling(m_John.getHead().top);
		}
		else if (m_Thomas.getFeet().intersects(m_John.getHead())) // thomas on john
		{
			m_Thomas.stopFalling(m_John.getHead().top);
		}
		else if (m_John.getFeet().intersects(m_Bob.getHead())) // john on bob
		{
			m_John.stopFalling(m_Bob.getHead().top);
		}
		else if (m_John.getFeet().intersects(m_Thomas.getHead())) // john on thomas
		{
			m_John.stopFalling(m_Thomas.getHead().top);
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Thomas and Bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

	}// End if playing

	// Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}

	// Set the appropriate view around the appropriate character
	switch (m_LM.getCurrentLevel())
	{
	case 1:
		if (m_SplitScreen)
		{
			m_LeftView.setCenter(m_John.getCenter());
			m_RightView.setCenter(m_Bob.getCenter());
		}
		else
		{
			// Centre full screen around appropriate character
			if (m_Character1)
			{
				m_MainView.setCenter(m_John.getCenter());
			}
			else
			{
				m_MainView.setCenter(m_Bob.getCenter());
			}
		}
		break;

	case 2:
		if (m_SplitScreen)
		{
			m_LeftView.setCenter(m_Thomas.getCenter());
			m_RightView.setCenter(m_Bob.getCenter());
		}
		else
		{
			// Centre full screen around appropriate character
			if (m_Character1)
			{
				m_MainView.setCenter(m_Thomas.getCenter());
			}
			else
			{
				m_MainView.setCenter(m_Bob.getCenter());
			}
		}
		break;

	case 3:
		if (m_SplitScreen)
		{
			m_LeftView.setCenter(m_Thomas.getCenter());
			m_RightView.setCenter(m_John.getCenter());
		}
		else
		{
			// Centre full screen around appropriate character
			if (m_Character1)
			{
				m_MainView.setCenter(m_Thomas.getCenter());
			}
			else
			{
				m_MainView.setCenter(m_John.getCenter());
			}
		}
		break;

	case 4:
		if (m_SplitScreen)
		{
			m_LeftView.setCenter(m_Thomas.getCenter());
			m_RightView.setCenter(m_Bob.getCenter());
		}
		else
		{
			// Centre full screen around appropriate character
			if (m_Character1)
			{
				m_MainView.setCenter(m_Thomas.getCenter());
			}
			else
			{
				m_MainView.setCenter(m_Bob.getCenter());
			}
		}
		break;
	}

	// Time to update the HUD?
	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update game HUD text
		stringstream ssTime;
		stringstream ssLevel;

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the water, fire, and ice particle systems
	if (m_WaterParticles.running()) 
	{
		m_WaterParticles.update(dtAsSeconds);
	}
	if (m_FireParticles.running()) 
	{
		m_FireParticles.update(dtAsSeconds);
	}
	if (m_IceParticles.running()) 
	{
		m_IceParticles.update(dtAsSeconds);
	}
	if (m_GoalParticles.running())
	{
		m_GoalParticles.update(dtAsSeconds);
	}
}// End of update function
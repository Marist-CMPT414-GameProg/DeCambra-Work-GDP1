#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// Prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);

	// How long is this new time limit
	m_TimeRemaining = m_LM.getTimeLimit();

	// Determine characters based on the current level
	switch (m_LM.getCurrentLevel())
	{
	case 1:
		m_John.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);		
		break;

	case 2:
		m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);
		break;

	case 3:
		m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
		m_John.spawn(m_LM.getStartPosition(), GRAVITY);
		break;

	case 4:
		m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);
		break;
	}

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}
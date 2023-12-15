#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	// Update the shader parameters
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

	if (!m_SplitScreen)
	{
		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Draw the background, complete with shader effect
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the Level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		// Draw thomas
		if (m_LM.getCurrentLevel() == 2 || m_LM.getCurrentLevel() == 3 || m_LM.getCurrentLevel() == 4)
		m_Window.draw(m_Thomas.getSprite());

		// Draw bob
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 2 || m_LM.getCurrentLevel() == 4)
		m_Window.draw(m_Bob.getSprite());

		// Draw John
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 3)
		m_Window.draw(m_John.getSprite());

		// Draw the particle systems
		if (m_WaterParticles.running())
		{
			m_Window.draw(m_WaterParticles);
		}
		if (m_FireParticles.running())
		{
			m_Window.draw(m_FireParticles);
		}
		if (m_IceParticles.running())
		{
			m_Window.draw(m_IceParticles);
		}
		if (m_GoalParticles.running())
		{
			m_Window.draw(m_GoalParticles);
		}
	}
	else
	{
		// Split-screen view is active

		// First draw Thomas' side of the screen

		// Switch to background view
		m_Window.setView(m_BGLeftView);

		// Draw the background, complete with shader effect
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		// Switch to m_LeftView
		m_Window.setView(m_LeftView);

		// Draw the Level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		// Draw bob
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 2 || m_LM.getCurrentLevel() == 4)
		m_Window.draw(m_Bob.getSprite());

		// Draw thomas
		if (m_LM.getCurrentLevel() == 2 || m_LM.getCurrentLevel() == 3 || m_LM.getCurrentLevel() == 4)
		m_Window.draw(m_Thomas.getSprite());

		// Draw John
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 3)
		m_Window.draw(m_John.getSprite());

		// Draw the particle systems
		if (m_WaterParticles.running())
		{
			m_Window.draw(m_WaterParticles);
		}
		if (m_FireParticles.running())
		{
			m_Window.draw(m_FireParticles);
		}
		if (m_IceParticles.running())
		{
			m_Window.draw(m_IceParticles);
		}
		if (m_GoalParticles.running())
		{
			m_Window.draw(m_GoalParticles);
		}

		// Now draw Bob's side of the screen

		// Switch to background view
		m_Window.setView(m_BGRightView);

		// Draw the background, complete with shader effect
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		// Switch to m_RightView
		m_Window.setView(m_RightView);

		// Draw the Level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		// Draw bob
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 2 ||m_LM.getCurrentLevel() == 4)
		m_Window.draw(m_Bob.getSprite());

		// Draw thomas
		if (m_LM.getCurrentLevel() == 2 || m_LM.getCurrentLevel() == 3 || m_LM.getCurrentLevel() == 4)
		m_Window.draw(m_Thomas.getSprite());

		// Draw John
		if (m_LM.getCurrentLevel() == 1 || m_LM.getCurrentLevel() == 3)
		m_Window.draw(m_John.getSprite());

		// Draw the particle systems
		if (m_WaterParticles.running())
		{
			m_Window.draw(m_WaterParticles);
		}
		if (m_FireParticles.running())
		{
			m_Window.draw(m_FireParticles);
		}
		if (m_IceParticles.running())
		{
			m_Window.draw(m_IceParticles);
		}
		if (m_GoalParticles.running())
		{
			m_Window.draw(m_GoalParticles);
		}
	}

	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);
	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());
	if (!m_Playing)
	{
		m_Window.draw(m_Hud.getMessage());
	}

	// Show everything we have just drawn
	m_Window.display();
}
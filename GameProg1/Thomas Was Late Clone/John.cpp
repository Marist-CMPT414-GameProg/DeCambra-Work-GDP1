#include "John.h"
#include "TextureHolder.h"

John::John()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/john.png"));

	m_JumpDuration = .3;
}

// A virtual function
bool John::handleInput()
{
	m_JustJumped = false;

	if (WASD)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			// Start a jump if not already jumping
			// but only if standing on a block (not falling)
			if (!m_IsJumping && !m_IsFalling)
			{
				m_IsJumping = true;
				m_TimeThisJump = 0;
				m_JustJumped = true;
			}
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			m_LeftPressed = true;
		}
		else
		{
			m_LeftPressed = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			m_RightPressed = true;
		}
		else
		{
			m_RightPressed = false;
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			// Start a jump if not already jumping
			// but only if standing on a block (not falling)
			if (!m_IsJumping && !m_IsFalling)
			{
				m_IsJumping = true;
				m_TimeThisJump = 0;
				m_JustJumped = true;
			}
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			m_LeftPressed = true;
		}
		else
		{
			m_LeftPressed = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			m_RightPressed = true;
		}
		else
		{
			m_RightPressed = false;
		}
	}
	

	return m_JustJumped;
}

void John::onLevelChanged(int newLevel) 
{
	// Update controls based on the new level
	switch (newLevel) 
	{
	case 1:
		// Set controls for level 1 (WASD)
		WASD = true;
		break;
	case 2:
		// Set controls for level 2 (WASD)
		WASD = true;
		break;
	case 3:
		// Set controls for level 3 (Arrow keys)
		WASD = false;
		break;
	}
}
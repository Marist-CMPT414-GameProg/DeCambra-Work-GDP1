// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

// Function declaration
void updateEnemies(float elapsedTime, int enemyPositions[], bool enemyAlive[], float& enemySpeed, int& numAliveEnemies);

static int spawnedEnemies = 0;
const int NUM_ENEMIES = 7;
float enemySpeed = 235.0f;
Sprite enemies[NUM_ENEMIES];

// Increasing difficulty
int score = 0;
int currentLevel = 1;
float enemySpawnInterval = 1.0f;

// Rain
const int MAX_RAIN_DROPS = 500;
Sprite rain[MAX_RAIN_DROPS];

// Where is player?
enum class side {LEFT, RIGHT, NONE};

int main()
{
	// Create a video mode object
	// VideoMode vm(1920, 1080);

	// Low res code
	VideoMode vm(960, 540);

	// Create and open a window for the game
	// RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Low res code
	RenderWindow window(vm, "Timber!!!");
	View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	//End of low res code!! Everything else is the same!!

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Prepare the rain
	Texture textureRain;
	textureRain.loadFromFile("graphics/rain.png");
	float rainDelay = 0.0f;
	static int nextRaindropIndex = 0;

	for (int i = 0; i < MAX_RAIN_DROPS; i++)
	{
		rain[i].setTexture(textureRain);
	}

	// How fast does the rain fall?
	float rainSpeed = 400.0f;

	// Make 3 ships sprites
	Texture textureShip1;
	Texture textureShip2;
	Texture textureShip3;

	// Load 3 new textures
	textureShip1.loadFromFile("graphics/ship1.png");
	textureShip2.loadFromFile("graphics/ship2.png");
	textureShip3.loadFromFile("graphics/ship3.png");

	// 3 New sprites
	Sprite spriteShip1;
	Sprite spriteShip2;
	Sprite spriteShip3;
	spriteShip1.setTexture(textureShip1);
	spriteShip2.setTexture(textureShip2);
	spriteShip3.setTexture(textureShip3);

	// Position the ships on the left of the screen & at different heights
	spriteShip1.setPosition(0, 0);
	spriteShip2.setPosition(0, 250);
	spriteShip3.setPosition(0, 500);

	// Are the ships currently on screen?
	bool ship1Active = false;
	bool ship2Active = false;
	bool ship3Active = false;

	// How fast is each ship?
	float ship1Speed = 100.0f;
	float ship2Speed = 100.0f;
	float ship3Speed = 100.0f;

	// Define minimum and maximum scaling factors for the ships
	const float minScale = 0.25f;
	const float maxScale = 1.0f;

	// Initialize random scales for each ship
	float ship1Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));
	float ship2Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));
	float ship3Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

	// Variables to control time itself
	Clock clock;

	// Track whether the game is running
	bool paused = true;	

	// Draw some text
	sf::Text messageText;
	sf::Text scoreText;
	sf::Text levelText;

	// We need to choose a font
	sf::Font font;
	font.loadFromFile("fonts/Starjedi.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);
	levelText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score: 0");
	levelText.setString("LvL: " + std::to_string(currentLevel));

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	levelText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(Color::Green);
	scoreText.setFillColor(Color::Green);
	levelText.setFillColor(Color::Green);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(70, 20);
	levelText.setPosition(1400, 20);

	// Prepare the enemy
	Texture textureEnemy;
	textureEnemy.loadFromFile("graphics/enemy.png");
	int enemyPositions[NUM_ENEMIES];
	bool enemyAlive[NUM_ENEMIES];
	int numAliveEnemies = 0;

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		enemies[i].setTexture(textureEnemy);
		enemies[i].setPosition(-2000, -2000);
		enemyAlive[i] = false;
	}

	// Prepare the player
	Texture	texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(960, 764);
	spritePlayer.setOrigin(38.5, 0);

	// The player starts on the left
	side playerSide = side::LEFT;

	// Prepare the gravestone
	Texture	textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 830);

	// Prepare the axe
	Texture	textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(940, 890);
	spriteAxe.setRotation(45);
	spriteAxe.setScale(-1, 1);

	// Line the axe up with the player
	const float AXE_POSITION_LEFT = 940;
	const float AXE_POSITION_RIGHT = 960;
	bool axePositionLeft = false;
	bool axePositionRight = false;

	// Control the player input
	bool acceptInput = false;

	// Prepare the sound
	SoundBuffer lightsaberBuffer;
	lightsaberBuffer.loadFromFile("sound/lightsaber.wav");
	Sound lightsaber;
	lightsaber.setBuffer(lightsaberBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				if (axePositionLeft)
				{
					spriteAxe.setRotation(45);
				}
				else
				{
					spriteAxe.setRotation(-45);
				}
				// Listen for key presses again
				acceptInput = true;
			}
		}
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
	
		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
	
			// Reset the score and level and enemy speed
			score = 0;
			currentLevel = 1;
			levelText.setString("LvL: " + std::to_string(currentLevel));
			enemySpawnInterval = 1.0f;
			enemySpeed = 235.0f;
	
			// Hide all enemies
			for (int i = 0; i < NUM_ENEMIES; i++)
			{
				enemyAlive[i] = false;
				numAliveEnemies = 0;
			}

			// Reset the rain
			nextRaindropIndex = 0;
			rainDelay = 0.0f;
			for (int i = 0; i < MAX_RAIN_DROPS; i++)
			{
				rain[i].setPosition(-2000, -2000);
			}
	
			// Make sure the gravestone is hidden
			spriteRIP.setPosition(675, 2000);
		
			// Set axe position
			spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
			spriteAxe.setScale(-1, 1);
			axePositionRight = false;
			axePositionLeft = true;
			if (axePositionLeft)
			{
				spriteAxe.setRotation(45);
			}
			else
			{
				spriteAxe.setRotation(-45);
			}
				
			// Set player position
			spritePlayer.setOrigin(38.5, 0);
			spritePlayer.setPosition(960, 764);
			spritePlayer.setScale(1, 1);
			acceptInput = true;
		}
	
		// Wrap the player control to make sure we are accepting input
		if (acceptInput)
		{
			// Attack if space key is pressed
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				// Check if player hit enemy
				for (int i = 0; i < NUM_ENEMIES; i++)
				{
					float enemyX = enemies[i].getPosition().x;
					float playerX = spritePlayer.getPosition().x;
					float enemyHitDistanceX = 125.0f;

					float distanceFromPlayerX = std::abs(enemyX - playerX);

					if (enemyAlive[i] && distanceFromPlayerX <= enemyHitDistanceX)
					{
						if ((playerSide == side::LEFT && enemyPositions[i] < 5) || (playerSide == side::RIGHT && enemyPositions[i] > 5))
						{
							score++;
							enemyAlive[i] = false;
							numAliveEnemies--;							
						}
					}
				}

				// Axe swing
				if (axePositionLeft)
				{
					spriteAxe.setRotation(-45);
				}
				else
				{
					spriteAxe.setRotation(45);
				}
				acceptInput = false;

				// Play a lightsaber sound
				lightsaber.play();

				// Update levels based on score
				if (score >= currentLevel * 10)
				{
					currentLevel++;
					levelText.setString("LvL: " + std::to_string(currentLevel));

					enemySpeed += 100.0f;
					if (enemySpeed >= 700.0f)
					{
						// Cap enemy speed
						enemySpeed = 700.0f;
					}

					enemySpawnInterval -= 0.2f;
					if (enemySpawnInterval <= 0.4f)
					{
						// Cap enemy spawn interval
						enemySpawnInterval = 0.4f;
					}
				}
			}


			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Axe and player positioning
				axePositionLeft = false;
				axePositionRight = true;
				if (axePositionLeft)
				{
					spriteAxe.setRotation(45);
				}
				else
				{
					spriteAxe.setRotation(-45);
				}
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spriteAxe.setScale(1, 1);
				
				playerSide = side::RIGHT;
				
				spritePlayer.setPosition(960, 764);
				spritePlayer.setScale(-1, 1);
				
				acceptInput = false;
			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Axe and player positioning
				axePositionLeft = true;
				axePositionRight = false;
				if (axePositionLeft)
				{
					spriteAxe.setRotation(45);
				}
				else
				{
					spriteAxe.setRotation(-45);
				}
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spriteAxe.setScale(-1, 1);
				
				playerSide = side::LEFT;

				spritePlayer.setPosition(960, 764);
				spritePlayer.setScale(1, 1);

				acceptInput = false;
			}
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		if (!paused)
		{
			// Measure time
			Time dt = clock.restart();
			
			// Increment rainDelay
			rainDelay += dt.asSeconds();

			// Set the rain
			if (rainDelay >= 0.5f)
			{
				if (nextRaindropIndex < MAX_RAIN_DROPS)
				{
					// Where does the rain start
					float xAxis = static_cast<float>(rand() % 1920);
					float yAxis = 0.0f;
					rain[nextRaindropIndex].setPosition(xAxis, yAxis);

					nextRaindropIndex++;
					rainDelay = 0.0f;
				}
			}

			// Move all the rain drops
			for (int i = 0; i < nextRaindropIndex; i++)
			{
				rain[i].move(0, rainSpeed * dt.asSeconds());

				// Has rain reached the ground?
				if (rain[i].getPosition().y >= 930)
				{
					// Reset raindrop's position to the top
					float xAxis = static_cast<float>(rand() % 1920);
					rain[i].setPosition(xAxis, 0);
				}
			}

			// Manage the ships
			// Ship 1
			if (!ship1Active)
			{
				// How fast is the ship
				srand((int)time(0) * 10);
				ship1Speed = (rand() % 200);

				// How high is the ship
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteShip1.setPosition(-200, height);
				ship1Active = true;

				// Generate random scale factor between minScale and maxScale
				ship1Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

				// Update ship's scale
				spriteShip1.setScale(ship1Scale, ship1Scale);
			}
			else
			{
				spriteShip1.setPosition(spriteShip1.getPosition().x + (ship1Speed * dt.asSeconds()), spriteShip1.getPosition().y);

				// Has the ship reached the right hand edge of the screen?
				if (spriteShip1.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new ship next frame
					ship1Active = false;
				}
			}

			// ship 2
			if (!ship2Active)
			{
				// How fast is the ship
				srand((int)time(0) * 20);
				ship2Speed = (rand() % 200);

				// How high is the ship
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteShip2.setPosition(-200, height);
				ship2Active = true;

				// Generate random scale factor between minScale and maxScale
				ship2Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

				// Update ship's scale
				spriteShip2.setScale(ship1Scale, ship1Scale);
			}
			else
			{
				spriteShip2.setPosition(spriteShip2.getPosition().x + (ship2Speed * dt.asSeconds()), spriteShip2.getPosition().y);

				// Has the ship reached the right hand edge of the screen?
				if (spriteShip2.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new ship next frame
					ship2Active = false;
				}
			}

			// ship 3
			if (!ship3Active)
			{
				// How fast is the ship
				srand((int)time(0) * 30);
				ship3Speed = (rand() % 200);

				// How high is the ship
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteShip3.setPosition(-200, height);
				ship3Active = true;

				// Generate random scale factor between minScale and maxScale
				ship3Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

				// Update ship's scale
				spriteShip3.setScale(ship1Scale, ship1Scale);
			}
			else
			{
				spriteShip3.setPosition(spriteShip3.getPosition().x + (ship3Speed * dt.asSeconds()), spriteShip3.getPosition().y);

				// Has the ship reached the right hand edge of the screen?
				if (spriteShip3.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new ship next frame
					ship3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score: " << score;
			scoreText.setString(ss.str());

			// Update the enemy positions
			updateEnemies(dt.asSeconds(), enemyPositions, enemyAlive, enemySpeed, numAliveEnemies);
	
			// Has the player been killed by enemy?
			for (int i = 0; i < NUM_ENEMIES; i++)
			{
				float playerHitDistanceX = 1.0f; // Adjust this distance as needed
				float playerX = spritePlayer.getPosition().x;
				float enemyX = enemies[i].getPosition().x;

				float distanceFromPlayerX = std::abs(enemyX - playerX);

				if (enemyAlive[i] && distanceFromPlayerX < playerHitDistanceX)
				{
					// death
					paused = true;
					acceptInput = false;

					// Draw the gravestone
					spriteRIP.setPosition(900, 850);

					// hide the player & axe
					spritePlayer.setPosition(2000, 660);
					spriteAxe.setPosition(3000, spriteAxe.getPosition().y);

					// Change the text of the message
					messageText.setString("game over!");

					// Center it on the screen
					FloatRect textRect = messageText.getLocalBounds();

					messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

					messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				
					// Play the death sound
					death.play();
				}
			}
		}// End if(!pause)

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the ships
		window.draw(spriteShip1);
		window.draw(spriteShip2);
		window.draw(spriteShip3);

		// Draw the enemies
		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			if (enemyAlive[i])
			{
				window.draw(enemies[i]);
			}
		}
	
		// Draw the player
		window.draw(spritePlayer);
	
		// Draw the axe
		window.draw(spriteAxe);
	
		// Draw the RIP
		window.draw(spriteRIP);
	
		// Draw the rain
		if (!paused)
		{
			for (int i = 0; i < MAX_RAIN_DROPS; i++)
			{
				window.draw(rain[i]);
			}
		}		
	
		// Draw the score
		window.draw(scoreText);

		// Draw the level text
		window.draw(levelText);

		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Show everything we just drew
		window.display();
	}
	return 0;
}

void updateEnemies(float elapsedTime, int enemyPositions[], bool enemyAlive[], float& enemySpeed, int& numAliveEnemies)
{
    static float timeSinceLastMove = 0.0f;
    timeSinceLastMove += elapsedTime;

    if (timeSinceLastMove >= enemySpawnInterval && numAliveEnemies < NUM_ENEMIES)
    {
        // Find an inactive enemy slot and spawn a new enemy
        for (int i = 0; i < NUM_ENEMIES; i++)
        {
            if (!enemyAlive[i])
            {
                // Spawn a new enemy on a random side
                int randomSide = rand() % 2;
                float height = 850;

                if (randomSide == 0)
                {
					// Left side
                    enemyPositions[i] = 0;
                    enemies[i].setPosition(92.5, height);
                    enemies[i].setScale(-1, 1);
                }
                else
                {
					// Right side
                    enemyPositions[i] = 10;
                    enemies[i].setPosition(1827.5, height);
                    enemies[i].setScale(1, 1);
                }

                enemyAlive[i] = true;
                numAliveEnemies++;
                break; // Exit the loop after spawning an enemy
            }
        }

        timeSinceLastMove = 0.0f;
    }

    // Update the positions of all alive enemies
    for (int j = 0; j < NUM_ENEMIES; j++)
    {
        if (enemyAlive[j])
        {
            // Move the enemy based on its position
            if (enemyPositions[j] < 5)
            {
				// Left to right
                enemies[j].move(enemySpeed * elapsedTime, 0);
                enemies[j].setOrigin(0, 0);
            }
            else if (enemyPositions[j] > 5)
            {
				// Right to left
                enemies[j].move(-enemySpeed * elapsedTime, 0);
                enemies[j].setOrigin(0, 0);
            }

            // Check if an enemy has moved off-screen
            if (enemies[j].getPosition().x < -200 || enemies[j].getPosition().x > 2120)
            {
                // Reset the enemy's position and mark it as inactive
                enemies[j].setPosition(-2000, -2000);
                enemyAlive[j] = false;
                numAliveEnemies--;
            }
        }
    }
}
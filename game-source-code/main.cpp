/** \file main.cpp
		\brief Contains the main function

		NB:to document global objects (functions, typedefs, enum, macros, etc), you must document the file in which they are defined. That is, you must provide this file comment block.
 */

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "snake.h"

// Defining global constants						
const int gameWidth = 800; 						// The width of the game screen
const int gameHeight = 600;						// The height of the game screen
const sf::Vector2f snakeSize{20, 20};			// The dimensions of the paddle's rectangle
const float snakeSpeed = 200.f;					// The Snake's speed in the beginning of the game.

/** \fn int main()
 *  \brief This function contains the majority of the code for the game
 *
 *  \return The application exit code: 0 for successful completion; a negative number to indicate an error.
 */

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML SNAKE", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Create the Snake
	auto snake = sf::RectangleShape{};
	snake.setSize(snakeSize - sf::Vector2f(1, 1));
	snake.setOutlineThickness(3);
	snake.setOutlineColor(sf::Color::Blue);
	snake.setFillColor(sf::Color(100, 100, 200));
	snake.setOrigin(snakeSize / 2.f);

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("Welcome to SFML SNAKE!\nPress space to start the game");

	sf::Clock clock;
	sf::Clock moveTimer;
	bool isPlaying = false;
	bool isSnakeTriggered = false;

	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: Exit
			if ((event.type == sf::Event::Closed) ||
					((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			// Space key pressed: play
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				if (!isPlaying)
				{
					// (re)start the game
					isPlaying = true;
					clock.restart();

					// Reset the position of the paddles and ball
					snake.setPosition(gameWidth/2, gameHeight/2);
				}
			}
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();
			sf::Vector2f snakePos = snake.getPosition();

			//This if statement actually starts the game play by triggering the snake's movement.
			if(!isSnakeTriggered && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) | sf::Keyboard::isKeyPressed(sf::Keyboard::Down) | sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			{
				isSnakeTriggered = true;

			}
				

			if(isSnakeTriggered)
			{
				// if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (snake.getPosition().y > snake.getSize().y))
				// 	snake.move(0.f, -snakeSpeed * deltaTime);

				// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (snake.getPosition().y < gameHeight - snake.getSize().y))
				// 	snake.move(0.f, snakeSpeed * deltaTime);

				// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (snake.getPosition().x > snake.getSize().x))
				// 	snake.move(-snakeSpeed * deltaTime, 0.f);

				// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (snake.getPosition().x < gameWidth - snake.getSize().x))
				// 	snake.move(snakeSpeed * deltaTime, 0.f);
			}

		// Move the Snake
		// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (snake.getPosition().y > snake.getSize().y))
		// 	{
		// 		// snake.move(0.f, -snakeSpeed * deltaTime);
		// 		if(moveTimer.getElapsedTime().asSeconds() > 0.4f)
		// 		{
		// 			moveTimer.restart();
		// 			snake.setPosition(snakePos.x, snakePos.y - 10.f);
		// 		}
		// 		else
		// 		{
		// 			snake.setPosition(snakePos.x, snakePos.y);
		// 		}
		// 	}

		// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (snake.getPosition().y < gameHeight - snake.getSize().y))
		// 	{
		// 		snake.move(0.f, snakeSpeed * deltaTime);
		// 	}

		// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (snake.getPosition().x > snake.getSize().x))
		// 		snake.move(-snakeSpeed * deltaTime, 0.f);

		// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (snake.getPosition().x < gameWidth - snake.getSize().x))
		// 		snake.move(snakeSpeed * deltaTime, 0.f);
		}

		// Clear the window
		window.clear(sf::Color(50, 200, 50));

		if (isPlaying)
		{
			// Draw the snake
			window.draw(snake);
		}
		else
		{
			// Draw the pause message
			window.draw(pauseMessage);
		}

		// Display things on screen
		window.display();
	}

	return EXIT_SUCCESS;
}

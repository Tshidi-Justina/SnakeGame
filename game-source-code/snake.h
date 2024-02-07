#ifndef SNAKE
#define SNAKE

#include <SFML/Graphics.hpp>

const sf::Vector2f snakeSize{20, 20};

class Snake
{
public:
    Snake(){
        snakeBox.setSize(snakeSize - sf::Vector2f(1, 1));
        snakeBox.setOutlineThickness(3);
        snakeBox.setOutlineColor(sf::Color::Blue);
        snakeBox.setFillColor(sf::Color(100, 100, 200));
        snakeBox.setOrigin(snakeSize / 2.f);
    }

private:
    const sf::Vector2f snakeSize{20, 20};
	sf::RectangleShape snakeBox = sf::RectangleShape{};
};

#endif

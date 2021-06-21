#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <random>
class Wall
{
public:
	sf::Vector2f vertices[2];
	Wall();
	Wall(sf::Vector2f start, sf::Vector2f end);
};


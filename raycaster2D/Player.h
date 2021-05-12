#pragma once
#include <SFML/Graphics.hpp>
#include "Base.h"
class Player
{
public:
	sf::Vector2f position;
	float theta;
	int ray_density;
	sf::CircleShape player;

	Player();
	Player(sf::Vector2f pos, int density);
	sf::CircleShape getObject();
	void moveLeft(int distance);
	void moveRight(int distance);
	void moveUp(int distance);
	void moveDown(int distance);
};


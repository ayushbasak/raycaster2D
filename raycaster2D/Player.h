#pragma once
#include <SFML/Graphics.hpp>
#include "Base.h"
#include <vector>
class Player
{
public:
	/*
	* position	: player position
	* theta		: angle of first extruding from the player
	* angles	: angles of individual rays
	*/

	sf::Vector2f position;
	float theta;
	float del_angle;
	//std::vector<float> angles;
	int ray_density;
	sf::CircleShape player;

	Player();
	Player(sf::Vector2f pos, int density);

	sf::CircleShape getObject();

	void moveLeft(float distance);
	void moveRight(float distance);
	void moveUp(float distance);
	void moveDown(float distance);

	void rotateClockWise(float angle);
	void rotateAntiClockWise(float angle);


	//Returns exact coordinate of intersection between a ray and a wall

	sf::Vector2f intersection(sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f pos3, sf::Vector2f pos4);

	float distanceToIntersection(sf::Vector2f ray_begin, sf::Vector2f intersection);
};


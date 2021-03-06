#include "Player.h"
#include "Base.h"
Player::Player()
{
	this->position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	this->theta = 0.0f;
	this->ray_density = 10;
	this->del_angle = (VISUAL_ANGLE * 0.01745f) / this->ray_density;
	

	/*for (int i = 1; i <= this->ray_density; i++) {
		float del_angle = (VISUAL_ANGLE * 0.01745f) / this->ray_density;
		this->angles.push_back(this->theta + del_angle * i);
	}*/

	this->player.setRadius(PLAYER_RADIUS);
	this->player.setFillColor(sf::Color::White);
	this->player.setPosition(this->position);
}

Player::Player(sf::Vector2f pos, int density)
{
	this->position = pos;
	this->theta = 0.0f;
	this->ray_density = density;
	this->del_angle = (VISUAL_ANGLE * 0.01745f) / this->ray_density;
	
	
	/*for (int i = 1; i <= this->ray_density; i++) {
		float del_angle = (VISUAL_ANGLE * 0.01745f) / this->ray_density;
		this->angles.push_back(this->theta + del_angle * i);
	}*/

	this->player.setRadius(PLAYER_RADIUS);
	this->player.setFillColor(sf::Color::White);
	this->player.setPosition(this->position);
}

sf::CircleShape Player::getObject()
{
	return this->player;
};

void Player::moveLeft(float distance)
{
	this->position.x -= distance;
	if(this->position.x < 0.0f)
		this->position.x = 0.0f;
	this->player.setPosition(this->position);
}

void Player::moveRight(float distance)
{
	this->position.x += distance;
	if (this->position.x > WINDOW_WIDTH - PLAYER_RADIUS*2)
		this->position.x = WINDOW_WIDTH - PLAYER_RADIUS * 2;
	this->player.setPosition(this->position);
}

void Player::moveUp(float distance)
{
	this->position.y -= distance;
	if (this->position.y < 0.0f)
		this->position.y = 0.0f;
	this->player.setPosition(this->position);
}

void Player::moveDown(float distance)
{
	this->position.y += distance;
	if (this->position.y > WINDOW_HEIGHT - PLAYER_RADIUS * 2)
		this->position.y = WINDOW_HEIGHT - PLAYER_RADIUS * 2;
	this->player.setPosition(this->position);
}

void Player::rotateClockWise(float angle)
{
	this->theta += angle;
	if (theta >= 2 * PI)
		theta -= 2 * PI;

	/*for (int i = 0; i < this->ray_density;i++) {
		this->angles[i] += angle;
		if (this->angles[i] > 2 * PI)
			this->angles[i] -= 2 * PI;
	}*/
}

void Player::rotateAntiClockWise(float angle)
{
	this->theta -= angle;
	if (theta <= -2 * PI)
		theta += 2 * PI;

	//for (int i = 0; i < this->ray_density;i++) {
	//	this->angles[i] -= angle;
	//	if (this->angles[i] <= 2 * PI)
	//		this->angles[i] += 2 * PI;
	//}
}


/*
userexit's code
https://github.com/userexit/2D-RayCasting/blob/master/2D_RayCasting/ray.cpp
*/
sf::Vector2f Player::intersection(sf::Vector2f q1, sf::Vector2f q2, sf::Vector2f p3, sf::Vector2f p4)
{
	const sf::Vector2f p1 = q1;
	const sf::Vector2f p2 = q2;

	// Calculates denominator of equations
	const float den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

	if (den == 0)
		return { -1.f, -1.f };

	const float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / den;
	const float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / den;

	sf::Vector2f intersection_point = { -1.f, -1.f };
	if (t > 0 && t < 1 && u > 0 && u < 1)
	{
		// Gets intersection point
		intersection_point.x = p1.x + t * (p2.x - p1.x);
		intersection_point.y = p1.y + t * (p2.y - p1.y);
	}
	return intersection_point;
}

float Player::distanceToIntersection(sf::Vector2f ray_begin, sf::Vector2f intersection)
{
	float delta_x = (ray_begin.x - intersection.x);
	float delta_y = (ray_begin.y - intersection.y);

	return delta_x * delta_x + delta_y * delta_y;
}

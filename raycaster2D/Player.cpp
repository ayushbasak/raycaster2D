#include "Player.h"

Player::Player()
{
	this->position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	this->theta = 0.0;
	this->ray_density = 10;
	this->player.setRadius(PLAYER_RADIUS);
	this->player.setFillColor(sf::Color::White);
	this->player.setPosition(this->position);
}

Player::Player(sf::Vector2f pos, int density)
{
	this->position = pos;
	this->theta = 0.0;
	this->ray_density = density;
	this->player.setRadius(PLAYER_RADIUS);
	this->player.setFillColor(sf::Color::White);
	this->player.setPosition(this->position);
}

sf::CircleShape Player::getObject()
{
	return this->player;
};

void Player::moveLeft(int distance)
{
	this->position.x -= distance;
	this->player.setPosition(this->position);
}

void Player::moveRight(int distance)
{
	this->position.x += distance;
	this->player.setPosition(this->position);
}

void Player::moveUp(int distance)
{
	this->position.y -= distance;
	this->player.setPosition(this->position);
}

void Player::moveDown(int distance)
{
	this->position.x += distance;
	this->player.setPosition(this->position);
}


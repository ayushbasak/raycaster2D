#include "IO.h"
bool IO::left()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool IO::right()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

bool IO::up()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

bool IO::down()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

bool IO::cwr()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

bool IO::acwr()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}

#include "Wall.h"
#include "Base.h"
Wall::Wall()
{
	vertices[0] = sf::Vector2f(
		rand() % 500 + WINDOW_WIDTH/5.f,
		rand() % 500 + WINDOW_HEIGHT/5.f
	);
	vertices[1] = sf::Vector2f(
		rand() % 500 + WINDOW_HEIGHT/5.f,
		rand() % 500 + WINDOW_WIDTH/5.f
	);
}

Wall::Wall(sf::Vector2f start, sf::Vector2f end)
{
	vertices[0] = start;
	vertices[1] = end;
}

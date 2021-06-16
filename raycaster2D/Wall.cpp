#include "Wall.h"
#include <random>
#include <cstdlib>
#include <SFML/Graphics.hpp>
class Wall {
public:
	sf::Vector2f wall[2] = { sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f) };
	Wall() {
		srand(time(NULL));
		wall[0] = sf::Vector2f(rand() % 500 * 1.f, rand() % 500 * 1.f);
		wall[1] = sf::Vector2f(rand() % 500 * 1.f, rand() % 500 * 1.f);
	}
};
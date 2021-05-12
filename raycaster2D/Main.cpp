#include <SFML/Graphics.hpp>
#include "Base.h"
#include "Player.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raycaster2D");
	Player player1 = Player();
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player1.moveLeft(1);
		window.clear();
		window.draw(player1.getObject());
		window.display();
	}

	return 0;
}
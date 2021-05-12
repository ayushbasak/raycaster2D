#include <SFML/Graphics.hpp>
#include "Base.h"
#include "Player.h"
#include "IO.h"
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raycaster2D");
	Player player1 = Player(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 100);
	IO keyboard = IO();
	sf::Clock clock;
	while (window.isOpen()){
		float dt = clock.restart().asSeconds();
		//std::cout << dt << std::endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (keyboard.left())
			player1.moveLeft(SPEED * dt);
		else if (keyboard.right())
			player1.moveRight(SPEED * dt);
		else if (keyboard.up())
			player1.moveUp(SPEED * dt);
		else if (keyboard.down())
			player1.moveDown(SPEED * dt);

		if (keyboard.cwr())
			player1.rotateClockWise(ROTATION_SPEED * dt);
		else if (keyboard.acwr())
			player1.rotateAntiClockWise(ROTATION_SPEED * dt);
		window.clear();
		window.draw(player1.getObject());
		for (int i = 0; i < player1.ray_density; i++) {
			sf::Vector2f ray_begin(player1.position.x + PLAYER_RADIUS,
				player1.position.y + PLAYER_RADIUS);
			sf::Vector2f ray_end(player1.position.x + VISIBILITY * cos(player1.angles[i]),
				player1.position.y + VISIBILITY * sin(player1.angles[i]));

			sf::Vertex line[] = { ray_begin, ray_end };
			window.draw(line, 2, sf::Lines);
		}
		window.display();
	}

	return 0;
}
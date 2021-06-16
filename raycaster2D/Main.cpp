#include <SFML/Graphics.hpp>
#include "Base.h"
#include "Player.h"
#include "IO.h"
#include <random>
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raycaster2D");
	Player player1 = Player(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 100 );

	
	sf::Vertex testWall[] = {
		sf::Vector2f(40.0f, 300.0f),
		sf::Vector2f(500.0f, 100.0f)
	};
	
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

		if (keyboard.exit())
			return EXIT_SUCCESS;

		if (keyboard.left())
			player1.moveLeft(SPEED * dt);
		if (keyboard.right())
			player1.moveRight(SPEED * dt);
		if (keyboard.up())
			player1.moveUp(SPEED * dt);
		if (keyboard.down())
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
			float dist = 8000.f;
			
			//sf::Vector2f newPosition = player1.intersection(ray_begin, ray_end, testWall[0], testWall[1]);	

			sf::Vector2f newPosition = player1.intersection(ray_begin, ray_end, sf::Vector2f(40, 300), sf::Vector2f(500, 100));

			if (newPosition.x > 0.0f)
				ray_end = newPosition;
			
			sf::Vertex line[] = { sf::Vertex(ray_begin), sf::Vertex(ray_end) };
			window.draw(line, 2, sf::Lines);
		}
		window.draw(testWall, 2, sf::Lines);
		window.display();
	}

	return 0;
}
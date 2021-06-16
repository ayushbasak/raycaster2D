#include <SFML/Graphics.hpp>
#include "Base.h"
#include "Player.h"
#include "IO.h"
#include <iostream>
#include "Wall.cpp"
int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raycaster2D");
	Player player1 = Player(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 100 );

	Wall w1 = Wall();
	std::cout << w1.wall[0].x;

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
			
			sf::Vector2f newPosition = player1.intersection(ray_begin, ray_end, w1.wall[0] , w1.wall[1]);
			//std::cout << testWall[0];
			//sf::Vector2f newPosition = player1.intersection(ray_begin, ray_end, sf::Vector2f(40, 300), sf::Vector2f(500, 100));

			if (newPosition.x > 0.0f)
				ray_end = newPosition;
			
			sf::Vertex line[] = { sf::Vertex(ray_begin), sf::Vertex(ray_end) };
			window.draw(line, 2, sf::Lines);
		}
		sf::Vertex wall[] = { w1.wall[0], w1.wall[1] };
		window.draw(wall, 2, sf::Lines);
		window.display();
	}

	return 0;
}
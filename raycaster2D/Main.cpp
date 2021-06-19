#include <SFML/Graphics.hpp>
#include "Base.h"
#include "Player.h"
#include "IO.h"
#include <iostream>
#include <climits>
#include "Wall.h"

int main()
{
	srand((unsigned int)time(NULL));

	sf::RenderWindow window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Raycaster2D"
	);
	window.setVerticalSyncEnabled(true);
	Player player1 = Player(
		sf::Vector2f(
			WINDOW_WIDTH / 2,
			WINDOW_HEIGHT / 2
		),
		RAY_DENSITY
	);

	std::vector<Wall> multiWallSystem;

	for (int i = 0; i < WALL_COUNT;i++) {
		Wall w = Wall();
		multiWallSystem.push_back(w);
	}

	IO keyboard = IO();
	sf::Clock clock;


	while (window.isOpen()){

		float dt = clock.restart().asSeconds();
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
			sf::Vector2f ray_begin(
				player1.position.x + PLAYER_RADIUS,
				player1.position.y + PLAYER_RADIUS
			);
			sf::Vector2f ray_end(
				player1.position.x + VISIBILITY * cos(player1.angles[i]),
				player1.position.y + VISIBILITY * sin(player1.angles[i])
			);

			float dist = 8000.f;
			
			sf::Vector2f newPosition = { 0.0f, 0.0f };
			float maximumRenderDistance = FLT_MAX;

			for (int j = 0; j < WALL_COUNT;j++) {
				sf::Vector2f temporaryNewPosition = 
					player1.intersection(
						ray_begin,
						ray_end,
						multiWallSystem[j].vertices[0],
						multiWallSystem[j].vertices[1]
					);
				
				if (temporaryNewPosition.x < 0.0)
					continue;

				float distance = player1.distanceToIntersection(
					ray_begin,
					temporaryNewPosition
				);

				if (distance < maximumRenderDistance) {
					maximumRenderDistance = distance;
					newPosition = temporaryNewPosition;
				}
			}
			
			if (newPosition.x > 0.0f)
				ray_end = newPosition;
			
			sf::Vertex line[] = {
				sf::Vertex(
					ray_begin,
					sf::Color(202, 204, 129)
				),
				sf::Vertex(
					ray_end,
					sf::Color(93, 94, 60)
				)
			};
			window.draw(line, 2, sf::Lines);
		}
		for (int i = 0; i < WALL_COUNT;i++) {
			sf::Vertex wall[] = {
				sf::Vertex(multiWallSystem[i].vertices[0], sf::Color(165, 255, 38)),
				sf::Vertex(multiWallSystem[i].vertices[1], sf::Color(38, 252, 252))
			};
			
			window.draw(wall, 2, sf::Lines);
		}
		window.display();
	}

	return 0;
}
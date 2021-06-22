#include <SFML/Graphics.hpp>
//#include <nlohmann/json.hpp>

#include <algorithm>
//#include <fstream>

#include "Base.h"
#include "Player.h"
#include "IO.h"
#include <iostream>
#include <climits>
#include "Wall.h"

int main()
{
	srand((unsigned int)time(NULL));

	/*nlohmann::json j;
	std::ifstream input("configs.json");
	input >> j;

	std::cout << j["name"] << std::endl;*/

	sf::RenderWindow window(
		sf::VideoMode(WINDOW_WIDTH * 2, WINDOW_HEIGHT),
		"Raycaster2D"
	);

	//sf::RenderWindow render3D(
	//	sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
	//	"Raycaster3D"
	//);

	window.setVerticalSyncEnabled(true);
	Player player1 = Player(
			{
				WINDOW_WIDTH / 2,
				WINDOW_HEIGHT / 2
			}
		,
		RAY_DENSITY
	);

	std::vector<Wall> multiWallSystem;

	for (int i = 0; i < WALL_COUNT;i++) {
		Wall w = Wall();
		multiWallSystem.push_back(w);
	}

	Wall left = Wall({ 1.0f, 0.0f }, {1.0f, WINDOW_HEIGHT * 1.0f});
	Wall bottom = Wall({ 0.0f, WINDOW_HEIGHT * 1.0f }, { WINDOW_WIDTH * 1.0f, WINDOW_HEIGHT * 1.0f });
	Wall right = Wall({ WINDOW_WIDTH * 1.0f, 0.0f }, { WINDOW_WIDTH * 1.0f, WINDOW_HEIGHT * 1.0f });
	Wall top = Wall({ 0.0f, 1.0f }, { WINDOW_WIDTH * 1.0f, 1.0f});

	multiWallSystem.push_back(left);
	multiWallSystem.push_back(bottom);
	multiWallSystem.push_back(right);
	multiWallSystem.push_back(top);

	IO keyboard = IO();
	sf::Clock clock;


	/*
	TEST SYSTEM for Raycaster 3D
	*/
	float TEXTURE_WIDTH = WINDOW_WIDTH / RAY_DENSITY;
	/*sf::RectangleShape walls3D[RAY_DENSITY];

	for (int i = 0; i < RAY_DENSITY;i++) {
		walls3D[i].setSize({ TEXTURE_WIDTH, 100 });
		walls3D[i].setPosition({ TEXTURE_WIDTH * i + 0.0f  ,0.0f });
		walls3D[i].setFillColor(sf::Color(100, 100, 100));
	}*/


	sf::RectangleShape block;

	sf::Vertex flooring[] = {
		sf::Vertex({WINDOW_WIDTH, WINDOW_HEIGHT / 2}, sf::Color(54, 0, 69)),
		sf::Vertex({WINDOW_WIDTH * 2, WINDOW_HEIGHT / 2}, sf::Color(54, 0, 69)),
		sf::Vertex({WINDOW_WIDTH * 2, WINDOW_HEIGHT}, sf::Color(95, 4, 120)),
		sf::Vertex({WINDOW_WIDTH, WINDOW_HEIGHT}, sf::Color(95, 4, 120)),
	};

	sf::Vertex ceiling[] = {
		sf::Vertex({WINDOW_WIDTH, 0.0f}, sf::Color(241, 255, 150)),
		sf::Vertex({WINDOW_WIDTH * 2, 0.0f}, sf::Color(241, 255, 150)),
		sf::Vertex({WINDOW_WIDTH * 2, WINDOW_HEIGHT / 2}, sf::Color(140, 148, 87)),
		sf::Vertex({WINDOW_WIDTH, WINDOW_HEIGHT / 2}, sf::Color(140, 148, 87)),
	};

	//sf::RectangleShape floor;
	//floor.setFillColor(sf::Color(54, 0, 69));
	//floor.setPosition({ WINDOW_WIDTH, WINDOW_HEIGHT /2 });
	//floor.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT  / 2});

	//sf::RectangleShape ceiling;
	//ceiling.setFillColor(sf::Color(241, 255, 150));
	//ceiling.setPosition({ WINDOW_WIDTH, 0.0f });
	//ceiling.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT / 2 });

	while (window.isOpen()){

		window.clear();
		
		float closestWall = FLT_MAX;
		float dt = clock.restart().asSeconds();
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.draw(flooring, 4, sf::Quads);
		window.draw(ceiling, 4, sf::Quads);

		/*window.draw(floor);
		window.draw(ceiling);*/

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

		window.draw(player1.getObject());
		//std::cout << cos(player1.theta + 5 * player1.del_angle) << std::endl;
		for (int i = 0; i < player1.ray_density; i++) {
			sf::Vector2f ray_begin(
				player1.position.x + PLAYER_RADIUS,
				player1.position.y + PLAYER_RADIUS
			);


			float currentRayAngle = player1.theta + player1.del_angle * i;
			//std::cout << currentRayAngle << std::endl;
			


			sf::Vector2f ray_end(

				player1.position.x + VISIBILITY * cos(currentRayAngle),
				player1.position.y + VISIBILITY * sin(currentRayAngle)
			);

			//float dist = 8000.f;
			
			sf::Vector2f newPosition = { 0.0f, 0.0f };
			float maximumRenderDistance = FLT_MAX;

			for (int j = 0; j < WALL_COUNT + 4;j++) {
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
			//std::cout << maximumRenderDistance << std::endl;
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
			closestWall = std::min(closestWall, maximumRenderDistance);

			block.setFillColor(sf::Color::White);
			if (maximumRenderDistance == FLT_MAX)
				maximumRenderDistance = 0.0f;
			
			//float slope1 = ta/*n(currentRayAngle);

			//float slope2 = ()*/


			//maximumRenderDistance = (maximumRenderDistance * cos(currentRayAngle));
			
			float renderHeight = 0.0f;
			if(maximumRenderDistance > 0.0f)
			renderHeight = 509.2f * atan(200.0f / sqrt(maximumRenderDistance));

			block.setSize({ TEXTURE_WIDTH, renderHeight});
			block.setPosition({ i * TEXTURE_WIDTH + WINDOW_WIDTH, WINDOW_HEIGHT /2 - renderHeight/2 });
			int color = (int)(255 * 
					((1000.0f - sqrt(maximumRenderDistance)) / 1000.0f ) *
					((1000.0f - sqrt(maximumRenderDistance)) / 1000.0f)
				);
			block.setFillColor(sf::Color(
				color,
				(int) color/2,
				(int)color/2)
			);
			window.draw(block);


			//walls3D[i].setSize({ TEXTURE_WIDTH, 10000000.0f / maximumRenderDistance });
			//walls3D[i].setPosition({ walls3D[i].getPosition().x, 1000000.0f / (maximumRenderDistance * 2) });
			//int distColor = (int)((10000000.0f / maximumRenderDistance));
			//distColor = distColor > 255 ? 255 : distColor;
			//walls3D[i].setFillColor(sf::Color(distColor, distColor, distColor));
			////std::cout << walls3D[i].getSize().x;
			//render3D.draw(walls3D[i]);
		}

		for (int i = 0; i < WALL_COUNT + 4;i++) {
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
#pragma once
#include <SFML/Graphics.hpp>
class IO
{
public:

	bool left();
	bool right();
	bool up();
	bool down();
	bool cwr(); // clockwise rotation
	bool acwr(); // anti-clockwise rotation
};


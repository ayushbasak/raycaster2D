#pragma once
#include <SFML/Graphics.hpp>
class IO
{
public:

	bool left();
	bool right();
	bool up();
	bool down();

	/* ClockWise and AntiClockWise rotation */
	bool cwr();
	bool acwr();

	bool exit();
};


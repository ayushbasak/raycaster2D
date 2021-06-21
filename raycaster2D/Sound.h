#pragma once
#include <SFML/Audio.hpp>
class Sound
{
public:
	sf::SoundBuffer backgroundBuffer;
	sf::Sound backgroundMusic;
	Sound();
};

/*

sf::Sound backgroundMusic;
backgroundMusic.setBuffer(backgroundBuffer);

backgroundMusic.play();
backgroundMusic.setLoop(true);

*/

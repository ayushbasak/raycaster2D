#include "Sound.h"

Sound::Sound()
{
	if (this->backgroundBuffer.loadFromFile("res/120Hz.wav")) {
		backgroundMusic.setBuffer(backgroundBuffer);
		backgroundMusic.play();
		backgroundMusic.setLoop(true);

	}
}

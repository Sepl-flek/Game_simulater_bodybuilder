#include "Engine.h"

int main()
{
	sf::Music backgroundmusic;
	backgroundmusic.openFromFile("sound/Gameplay.wav");

	backgroundmusic.setVolume(20);
	backgroundmusic.setLoop(true);
	backgroundmusic.play();


    Engine myGame;

    myGame.run();

    return 0;
}
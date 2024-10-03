#include "Engine.h"

void Engine::input()
{
	sf::Event event_play;
	while (window->pollEvent(event_play))
	{
		if (event_play.key.code == sf::Keyboard::Escape) { window->close(); }
	}
}

void Engine::update(sf::Time const& deltaTime)
{
}

void Engine::draw()
{
	window->clear();
	window->draw(background);
	window->display();
}

Engine::Engine()
{
	background.setTexture(&AssetManager::GetTexture("image/background.jpg"));
	
}

void Engine::run()
{
	sf::Clock clock;

	while (window->isOpen())
	{
		sf::Time dt = clock.restart();

		input();

		update(dt);

		draw();
	}
}




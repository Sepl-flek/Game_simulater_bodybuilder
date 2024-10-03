#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
class Engine
{

	// ��������� ��������� ����������
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(),
		L"����������", sf::Style::Fullscreen);
	sf::RectangleShape background = sf::RectangleShape(
	sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	sf::Texture background_texture;

	void input();
	void update(sf::Time const & deltaTime);
	void draw();

public:
	Engine();
	void run();
};


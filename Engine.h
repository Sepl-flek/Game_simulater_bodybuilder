#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
#include "GameMenu.h"
#include <SFML/Audio.hpp>
#include "Person.h"
class Engine
{
	AssetManager manager; // менеджер ресурсов
	
	Person person = Person(1);
	
	// возможные доработки ращрешения
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(),
		L"БОДИБИЛДЕР", sf::Style::Fullscreen);

	// главное меню
	
	sf::RectangleShape background = sf::RectangleShape(
	sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	float width = sf::VideoMode::getDesktopMode().width;
	float heght = sf::VideoMode::getDesktopMode().height;

	//Текст для главного Экрана

	
	void setTextStyle(sf::Text& text, float x, float y, float size,const sf::Color &color, const std::string& content);

	//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

	// всй что связано с главным меню
	void GameMenu();
	void GamePlay();
	

	void input();
	void update(sf::Time const & deltaTime);
	void draw();


public:
	Engine();
	void run();
};


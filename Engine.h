#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
#include "GameMenu.h"
#include <SFML/Audio.hpp>
#include "Person.h"
#include "Collision.h"
#include "Food.h"
#include "location.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "load.h"

namespace fs = std::filesystem;
class Engine
{
	AssetManager manager; // менеджер ресурсов
	std::string filename = "D:/Visual-studio/projects/Game_body/saved_games";

	Person person = Person(1);
	
	// возможные доработки ращрешения
	//std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(),
	//	L"БОДИБИЛДЕР", sf::Style::Fullscreen);

	// главное меню
	
	sf::RectangleShape background = sf::RectangleShape(
	sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	
	//Текст для главного Экрана
	sf::Text text;
	
	void setTextStyle(sf::Text& text, float x, float y, float size,const sf::Color &color, const std::string& content);

	//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

	// всй что связано с главным меню
	void GameMenu();
	void GamePlay();
	void HomePlay(sf::RenderWindow& window);
	void FridgePlay(sf::RenderWindow& window);
	

	void input();
	void update(sf::Time const & deltaTime);
	void draw();

	sf::Music backgroundmusic;
	
	

	void LoadGame(sf::RenderWindow& window, Person& person);
	
	
public:
	Engine();
	void run();

};


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
class Engine
{
	AssetManager manager; // �������� ��������
	
	Person person = Person(1);
	
	// ��������� ��������� ����������
	//std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(),
	//	L"����������", sf::Style::Fullscreen);

	// ������� ����
	
	sf::RectangleShape background = sf::RectangleShape(
	sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;

	//����� ��� �������� ������
	sf::Text text;
	
	void setTextStyle(sf::Text& text, float x, float y, float size,const sf::Color &color, const std::string& content);

	//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

	// ��� ��� ������� � ������� ����
	void GameMenu();
	void GamePlay();
	void HomePlay(sf::RenderWindow& window);
	void FridgePlay(sf::RenderWindow& window);
	

	void input();
	void update(sf::Time const & deltaTime);
	void draw();

	sf::Music backgroundmusic;
	
public:
	Engine();
	void run();

};


#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "AssetManager.h"
#include "GameMenu.h"
class Engine
{
	AssetManager manager; // �������� ��������
	

	// ��������� ��������� ����������
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(),
		L"����������", sf::Style::Fullscreen);

	// ������� ����
	
	sf::RectangleShape background = sf::RectangleShape(
	sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	float width = sf::VideoMode::getDesktopMode().width;
	float heght = sf::VideoMode::getDesktopMode().height;

	//����� ��� �������� ������

	
	void setTextStyle(sf::Text& text, float x, float y, float size,const sf::Color &color, const std::string& content);

	//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

	// ��� ��� ������� � ������� ����
	void GameMenu();

	void input();
	void update(sf::Time const & deltaTime);
	void draw();


public:
	Engine();
	void run();
};


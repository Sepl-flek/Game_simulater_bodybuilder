#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
class Food
{
public:
	Food(float x, float y, sf::Vector2f position,std::string texture, int coast, float scaleX, float scaleY, int satiety ,float width = 77, float height = 77 );
	void draw(sf::RenderWindow& window);
	void change_color(sf::Color color);
	int get_coast();
	int get_satiety();
private:

	sf::Sprite food;
	sf::RectangleShape border;
	int coast = 0;
	int satiety = 10; //насыщения
};


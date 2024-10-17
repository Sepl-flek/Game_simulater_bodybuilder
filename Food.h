#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
class Food
{
public:
	Food(float x, float y, sf::Vector2f position,std::string texture, int coast, float scaleX, float scaleY,float width = 77, float height = 77 );
	void draw(sf::RenderWindow& window);
	void change_color(sf::Color color);
private:

	sf::Sprite food;
	sf::RectangleShape border;
	int coast = 0;
};


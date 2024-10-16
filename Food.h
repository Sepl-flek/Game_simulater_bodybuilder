#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
class Food
{
public:
	Food(float x, float y, sf::Vector2f position,std::string texture,float width = 50, float height = 50);
	void draw(sf::RenderWindow& window);
	
private:
	sf::Sprite food;
};


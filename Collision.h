#pragma once
#include "Person.h"
#include <SFML/Audio.hpp>
class Collision
{
public:
	Collision(float x, float y,float width,float height);
	bool collision(Person &person);
	void change_color(const sf::Color &color);
	sf::RectangleShape get_rect();


private:
	sf::RectangleShape rect;
	sf::FloatRect collisia;
	float x, y, width, height;
	
};


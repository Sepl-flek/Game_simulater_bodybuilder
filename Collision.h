#pragma once
#include "Person.h"
class Collision
{
public:
	Collision(float x, float y,float width,float height);
	bool collision(Person person);
	bool collisionX(float person_x);
	bool collisionY(float person_y);

private:
	sf::FloatRect rect;
	float x, y, width, height;

};

